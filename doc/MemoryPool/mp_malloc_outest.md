
[< `mempool_t`](MemoryPool.md)

## `mp_malloc_outest`

### Definition
```C
void *mp_malloc_outest(mempool_t *self, size_t s);
```
Allocate a block of memory and store it into the outest scope, i.e., scope `#1`.

### Parameters
`self` The memory pool.
`s` The size to allocate.

### Return Value
The pointer of allocated memory.

### See Also
[`mp_malloc`](mp_malloc.md)
