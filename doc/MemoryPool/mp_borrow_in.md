
[< `mempool_t`](MemoryPool.md)

## `mp_borrow_in`

### Definition
```C
void mp_borrow_in(mempool_t *self, void *ptr);
```
Borrow the `ptr` from the outer scope to the current scope.

### Parameters
`self` The memory pool.
`ptr` The pointer to borrow.

### Return Value
None.

### See Also
[`mp_borrow_out`](mp_borrow_out.md)
