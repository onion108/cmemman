#include "../include/memman.h"
#include <stdlib.h>
#include <stdio.h>

#define SELF mempool_t *self

mempool_t* make_pool() {
    // Make a new pool
    mempool_t* pool = (mempool_t*) malloc(sizeof(mempool_t));

    // Initialize the scope depth
    pool->scope_depth = 0;

    // Initialize the pointer
    pool->ptr_pool = NULL;
    return pool;
}

void destroy_pool(SELF) {
    // Exit scope
    while (self->scope_depth) {
        fprintf(stderr, "libcmemman: warning: scope %d never exits until destroying the pool.", self->scope_depth);
        mp_exit_scope(self);
    }
    free(self->ptr_pool);
    free(self);
}

void mp_enter_scope(SELF) {
    #ifdef __DEBUG__
    printf("Entering scope %d\n", self->scope_depth + 1);
    #endif
    if (self->scope_depth == 0) {
        self->scope_depth = 1;
        self->ptr_pool = (ptr_info_t**)malloc(sizeof(ptr_info_t*));
        self->ptr_pool[0] = (ptr_info_t*)malloc(sizeof(ptr_info_t));
        self->ptr_pool[0][0].ptr = NULL;
    } else {
        self->scope_depth++;
        self->ptr_pool = (ptr_info_t**)realloc(self->ptr_pool, sizeof(ptr_info_t*) * self->scope_depth);
        self->ptr_pool[self->scope_depth-1] = (ptr_info_t*)malloc(sizeof(ptr_info_t));
        self->ptr_pool[self->scope_depth-1][0].ptr = NULL;
    }
}

int prv_mp_get_size_of_scope(SELF, int scope_id) {
    int c = 0;
    while(self->ptr_pool[scope_id][c].ptr) c++;
    return c;
}

void prv_mp_add_ptr_to_scope(SELF, int scope_id, void* ptr) {
    int len = prv_mp_get_size_of_scope(self, scope_id); 
    self->ptr_pool[scope_id] = (ptr_info_t*)realloc(self->ptr_pool[scope_id], (len + 2) * sizeof(ptr_info_t));
    self->ptr_pool[scope_id][len].ptr = ptr;
    self->ptr_pool[scope_id][len].destructor = NULL;
    self->ptr_pool[scope_id][len+1].ptr = NULL;
}

int prv_mp_get_index_of_ptr(SELF, int scope_id, void *ptr) {
    int len = prv_mp_get_size_of_scope(self, scope_id);
    for (int i = 0; i < len; i++) {
        if (self->ptr_pool[scope_id][i].ptr == ptr) {
            return i;
        }
    }
    return -1;
}

void prv_mp_remove_ptr_from_scope(SELF, int scope_id, void* ptr) {
    int idx = prv_mp_get_index_of_ptr(self, scope_id, ptr);
    int len = prv_mp_get_size_of_scope(self, scope_id);
    if (idx == -1) {
        fprintf(stderr, "libmemman: warning: trying to remove pointer (%p) that doesn't exist in scope %d", ptr, scope_id);
        return;
    }
    self->ptr_pool[scope_id][idx].ptr = NULL;
    for (int i = idx; i < len; i++) {
        self->ptr_pool[scope_id][i].ptr = self->ptr_pool[scope_id][i+1].ptr;
        self->ptr_pool[scope_id][i].destructor = self->ptr_pool[scope_id][i+1].destructor;
    }
}

void mp_borrow_out(SELF, void* ptr) {
    if (self->scope_depth <= 1) {
        return;
    }
    void *p = ptr;
    prv_mp_remove_ptr_from_scope(self, self->scope_depth-1, p);
    prv_mp_add_ptr_to_scope(self, self->scope_depth-2, p);
}

void mp_exit_scope(SELF) {
    #ifdef __DEBUG__
    printf("\nExiting scope %d\n", self->scope_depth);
    #endif
    int len = prv_mp_get_size_of_scope(self, self->scope_depth-1);
    for (int i = 0; i < len; i++) {
        #ifdef __DEBUG__
        printf("Freeing %p\n", self->ptr_pool[self->scope_depth-1][i].ptr);
        #endif
        if (self->ptr_pool[self->scope_depth-1][i].destructor != NULL) {
            self->ptr_pool[self->scope_depth-1][i].destructor(self->ptr_pool[self->scope_depth-1][i].ptr);
        }
        free(self->ptr_pool[self->scope_depth-1][i].ptr);
    }
    free(self->ptr_pool[self->scope_depth-1]);
    self->scope_depth--;

}

void mp_borrow_in(SELF, void *ptr) {
    if (self->scope_depth <= 1) {
        return;
    }
    void *p = ptr;
    prv_mp_remove_ptr_from_scope(self, self->scope_depth-2, p);
    prv_mp_add_ptr_to_scope(self, self->scope_depth-1, p);
}

void *mp_malloc(SELF, size_t size) {
    if (self->scope_depth == 0) {
        fprintf(stderr, "libcmemman: fatal: trying to allocate memory without enterning any scope.");
        destroy_pool(self);
        exit(-1);
    }
    void *result = malloc(size);
    prv_mp_add_ptr_to_scope(self, self->scope_depth-1, result);
    return result;
}

void *mp_malloc_outest(SELF, size_t size) {
    if (self->scope_depth == 0) {
        fprintf(stderr, "libcmemman: fatal: trying to allocate memory without enterning any scope.");
        destroy_pool(self);
        exit(-1);
    }
    void *result = malloc(size);
    prv_mp_add_ptr_to_scope(self, 0, result);
    return result;
}

void mp_register_destructor(SELF, void* ptr, destructor_t dest) {
    // Get the index of the pointer
    int idx = prv_mp_get_index_of_ptr(self, self->scope_depth-1, ptr);
    if (idx == -1) {
        fprintf(stderr, "libmemman: warning: trying to remove pointer (%p) that doesn't exist in scope %d", ptr, self->scope_depth-1);
        return;
    }
    
    // Register the destructor
    self->ptr_pool[self->scope_depth-1][idx].destructor = dest;
}
