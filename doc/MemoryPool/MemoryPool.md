[< Overview](../Overview.md)

## `mempool_t`

### Definition
```C
typedef struct _memory_pool {
    void ***ptr_pool;
    int scope_depth;
} mempool_t;
```

### Members
```C
void ***ptr_pool;
```
The pool that stores pointers.

```C
int scope_depth;
```
The id of current scope. To access the memory pool of current scope, we use `ptr_pool[scope_depth-1]`.

### Associated Methods

#### Constructor
```C
mempool_t* make_pool();
```
[Learn More >](make_pool.md)

#### Destructor
```C
void destroy_pool(mempool_t*);
```
[Learn More >](destroy_pool.md)

#### Scope Managing
```C
void mp_enter_scope(mempool_t*);
```
[Learn More >](mp_enter_scope.md)
```C
void mp_exit_scope(mempool_t*);
```
[Learn More >](mp_exit_scope.md)

#### Pointer Borrowing
```C
void mp_borrow_out(mempool_t*, void*);
```
[Learn More >](mp_borrow_out.md)
```C
void mp_borrow_in(mempool_t*, void*);
```
[Learn More >](mp_borrow_in.md)
#### Memory Allocating
```C
void *mp_malloc(mempool_t*, size_t);
```
[Learn More >](mp_malloc.md)
