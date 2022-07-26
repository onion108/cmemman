[< `mempool_t`](MemoryPool.md)

## `mp_exit_scope`

### Definition
```C
void mp_exit_scope(mempool_t* self);
```
Exit the current scope.
> #### <a style="color:red">WARNING: Data Lose</a>
> This method will free all the memories allocated in the current scope. Make sure you have borrowed out all the memories you need before calling this method.

### Parameters
`self` The memory pool.

### Return Value
None.

### See Also
[`mp_enter_scope`](mp_enter_scope.md)
