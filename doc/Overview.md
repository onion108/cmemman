# CMemMan Documentation

Current documentation for: 1.0.0

## Overview

`libcmemman` is a library that provides some useful technologies for managing memory in a more efficient way in C.

## Types
```C
typedef struct _memory_pool {
    ptr_info_t **ptr_pool;
    int scope_depth;
} mempool_t;
```
[Learn More >](MemoryPool/MemoryPool.md)

```C
typedef void (*destructor_t)(void *);
```

```C
typedef struct _ptr_info {
    void *ptr;
    destructor_t destructor;
} ptr_info_t;
```

## Concepts

### Index
[B](#b)
[S](#s)

### B
[Borrow](Concepts/Borrow.md)
### S
[Scope](Concepts/Scope.md)
