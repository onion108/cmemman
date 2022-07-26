[< Overview](../Overview.md)

## Scope

### Definition

A **scope** is a space that stores some pointers to some memories that are dynamically allocated and the memories will be freed after exiting the scope.
Scopes can be have a tree-like structure. Look at the following structure which draws out some scopes and the relationships between them:
```
 /
 |  /
 |  |  /
 |  |  |  /
 |  | 3| 5|
 |  |  |  \
1| 2|  \
 |  |  /
 |  |  |
 |  | 4|
 |  |  \
 |  \
 \
```
In this case, the scope `#2` is the **Inner Scope** of the scope `#1`, and the scope `#1` is the **Outer Scope** of the scope `#2`. When we say **Outer Scope** and **Inner Scope** without objective, we mean the outer(inner) scope of the **Current Scope**. If the current scopes is `#2`, then the term **Outer Scope** means scope `#1` and the term **Inner Scopes** means scope `#3` and `#4`.

### See Also
[`mp_enter_scope`](../MemoryPool/mp_enter_scope.md)
[`mp_exit_scope`](../MemoryPool/mp_exit_scope.md)
