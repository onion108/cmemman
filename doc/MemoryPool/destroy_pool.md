[< `mempool_t`](MemoryPool.md)

## `destroy_pool`

### Definition
```C
void destroy_pool(mempool_t *self);
```

Destroy a `mempool_t` objects.

> #### <a style="color:red">WARNING: Data Lose</a>
> This method will free all the memories allocated in the pool and then free the pool itself. Make sure you are calling it at the end of the program.
 

### Parameters
`self` The pool object to destroy.

### Return Value
None.

### See Also
[`make_pool`](make_pool.md)

