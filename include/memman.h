#ifndef CC551FE8_D82A_487A_94B6_BB6D1175E56F
#define CC551FE8_D82A_487A_94B6_BB6D1175E56F

#include <stdlib.h>

typedef struct _memory_pool {
    void ***ptr_pool;
    int scope_depth;
} mempool_t;

/**
 * Makes a memory pool.
 * @returns The memory pool object.
 */
mempool_t* make_pool();

/**
 * Destroy a pool.
 * @param pool The pool to destroy.
 */
void destroy_pool(mempool_t*);

/**
 * Enter a scope.
 * @param pool The pool.
 */
void mp_enter_scope(mempool_t*);

/**
 * Borrow out the pointer of this scope and goto the previous scope.
 * @param pool The pool.
 * @param ptr The pointer to borrow out.
 */
void mp_borrow_out(mempool_t*, void*);
/**
 * Borrow in the pointer of the previous scope.
 * @param pool The pool.
 * @param ptr The pointer to borrow in.
 */
void mp_borrow_in(mempool_t*, void*);

/**
 * Exit the scope and free all the pointer of the scope.
 * @param pool The pool.
 */
void mp_exit_scope(mempool_t*);

/**
 * Allocate a block of memory and add it to the current scope.
 */
void *mp_malloc(mempool_t*, size_t);

#endif /* CC551FE8_D82A_487A_94B6_BB6D1175E56F */
