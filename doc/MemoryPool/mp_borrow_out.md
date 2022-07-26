
[< `mempool_t`](MemoryPool.md)

## `mp_borrow_out`

### Definition
```C
void mp_borrow_out(mempool_t *self, void *ptr);
```
Borrow the `ptr` from the current scope to the outer scope.

### Parameters
`self` The memory pool.
`ptr` The pointer to borrow.

### Return Value
None.

### See Also
[`mp_borrow_in`](mp_borrow_in.md)
