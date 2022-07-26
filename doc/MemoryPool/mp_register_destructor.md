
[< `mempool_t`](MemoryPool.md)

## `mp_register_destructor`

### Definition
```C
void mp_register_destructor(mempool_t *self, void *ptr, destructor_t dest);
```
Register a destructor for a given pointer, so the destructor will be called when the pointer will be freed in the associated methods of `mempool_t`.

### Parameters
`self` The memory pool.
`ptr` The pointer.
`dest` The destructor.

### Return Value
None.

