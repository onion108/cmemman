#ifndef _CMEMMAN_MEMMAN_H__
#define _CMEMMAN_MEMMAN_H__

#include <stddef.h>

typedef void (*destructor_t)(void *);

typedef struct _ptr_info {
	void *ptr;
	destructor_t destructor;
} ptr_info_t;

typedef struct _memory_pool {
	ptr_info_t **ptr_pool;
	int scope_depth;
} mempool_t;

/**
 * Makes a memory pool.
 * @returns The memory pool object.
 */
mempool_t *make_pool();

/**
 * Destroy a pool.
 * @param pool The pool to destroy.
 */
void destroy_pool(mempool_t *);

/**
 * Enter a scope.
 * @param pool The pool.
 */
void mp_enter_scope(mempool_t *);

/**
 * Borrow out the pointer of this scope and goto the previous scope.
 * @param pool The pool.
 * @param ptr The pointer to borrow out.
 */
void mp_borrow_out(mempool_t *, void *);

/**
 * Borrow in the pointer of the previous scope.
 * @param pool The pool.
 * @param ptr The pointer to borrow in.
 */
void mp_borrow_in(mempool_t *, void *);

/**
 * Exit the scope and free all the pointer of the scope.
 * @param pool The pool.
 */
void mp_exit_scope(mempool_t *);

/**
 * Allocate a block of memory and add it to the current scope.
 */
void *mp_malloc(mempool_t *, size_t);

/**
 * Allocate a block of memory to the scope #1.
 */
void *mp_malloc_outest(mempool_t *, size_t);

/**
 * Register a destructor for the given pointer. Notice that the pointer must be
 * in the current scope.
 */
void mp_register_destructor(mempool_t *, void *, destructor_t);

#endif // _CMEMMAN_MEMMAN_H__
