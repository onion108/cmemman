[< Overview](../Overview.md)

## `ptr_info_t`

### Definition
```C
typedef struct _ptr_info {
    void *ptr;
    destructor_t destructor;
} ptr_info_t;
```
An internal type to represent a pointer and its related information.
### Members
```C
void *ptr;
```
The pointer.

```C
destructor_t destructor;
```
The destructor of this pointer.

### Associated Methods
None.
