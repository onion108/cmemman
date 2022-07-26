
[< `mempool_t`](MemoryPool.md)

## `mp_malloc`

### Definition
```C
void *mp_malloc(mempool_t *self, size_t s);
```
Allocate a block of memory and store it into the pool of current scope.

### Parameters
`self` The memory pool.
`s` The size to allocate.

### Return Value
The pointer of allocated memory.

### See Also
[`mp_malloc_outest`](./mp_malloc_outest.md)
