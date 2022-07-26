#include "../include/memman.h"
#include <stdlib.h>
#include <stdio.h>

#define SELF mempool_t *self

mempool_t* make_pool() {
    mempool_t* pool = (mempool_t*) malloc(sizeof(mempool_t));
    pool->scope_depth = 0;
    return pool;
}

void destroy_pool(SELF) {
    for (int i = 0; i < self->scope_depth; i++) {
        while (self->ptr_pool[i]) {
            free(self->ptr_pool[i]);
            i++;
        }
        free(self->ptr_pool[i]);
    }
    free(self->ptr_pool);
    free(self);
}

void mp_enter_scope(SELF) {
    if (self->scope_depth == 0) {
        self->scope_depth = 1;
        self->ptr_pool = (void***)malloc(sizeof(void**));
        self->ptr_pool[0] = (void**)malloc(sizeof(void*));
        self->ptr_pool[0][0] = NULL;
    } else {
        self->scope_depth++;
        self->ptr_pool = (void***)realloc(self->ptr_pool, sizeof(void**) * self->scope_depth);
        self->ptr_pool[self->scope_depth-1] = (void**)malloc(sizeof(void*));
        self->ptr_pool[self->scope_depth-1][0] = NULL;
    }
}

int prv_mp_get_size_of_scope(SELF, int scope_id) {
    int c = 0;
    while(self->ptr_pool[scope_id][c]) c++;
    return c;
}

void prv_mp_add_ptr_to_scope(SELF, int scope_id, void* ptr) {
    int len = prv_mp_get_size_of_scope(self, scope_id); 
    self->ptr_pool[scope_id] = (void**)realloc(self->ptr_pool[scope_id], (len + 2) * sizeof(void*));
    self->ptr_pool[scope_id][len] = ptr;
    self->ptr_pool[scope_id][len+1] = NULL;
}

int prv_mp_get_index_of_ptr(SELF, int scope_id, void *ptr) {
    int len = prv_mp_get_size_of_scope(self, scope_id);
    for (int i = 0; i < len; i++) {
        if (self->ptr_pool[scope_id][i] == ptr) {
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
    self->ptr_pool[scope_id][idx] = NULL;
    for (int i = idx; i < len; i++) {
        self->ptr_pool[scope_id][i] = self->ptr_pool[scope_id][i+1];
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
        printf("Freeing %p\n", self->ptr_pool[self->scope_depth-1][i]);
        #endif
        free(self->ptr_pool[self->scope_depth-1][i]);
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
    void *result = malloc(size);
    prv_mp_add_ptr_to_scope(self, self->scope_depth-1, result);
    return result;
}

