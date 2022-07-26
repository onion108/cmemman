# CMemMan Documentation

Current documentation for: 1.0.0

## Overview

`libcmemman` is a library that provides some useful technologies for managing memory in a more efficient way in C.

## Structures
```C
typedef struct _memory_pool {
    void ***ptr_pool;
    int scope_depth;
} mempool_t;
```
[Learn More >](MemoryPool/MemoryPool.md)

## Concepts

### Index
[B](#b)
[S](#s)

### B
[Borrow](Concepts/Borrow.md)
### S
[Scope](Concepts/Scope.md)
