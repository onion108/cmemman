# CMemman: Your memory helper

As far as we know, the C Programming Language is a great language and have been widely used in almost everywhere. But there is a big problem that is the C is not **Memory-Safe**. For example, it's very common to encounter a problem called **Memory Leak** in C, which means you allocate a block of memory and forget to free it. Usually, it's not a big deal because the operating system will help you to collect the garbage. But it will be a serious problem if you run the program on a computer that have little memory, or if the program will run for a very long time. In this case, the program will "eat" more and more memories, and after the computer ran out of memory, the program will crash, and you will have to spend a lot of time to find the bug and also spend a lot of time to fix it.  
So the goal of this library is to help you with memory problems. Here is a simple example with CMemman:
```C
#include "/path/to/memman.h"
#include <stdio.h>
#include <stdlib.h>

int fun_that_moves_value(mempool_t* pool, int *value) {
    mp_enter_scope(pool);
    mp_borrow_in(pool, value);

    printf("%p = %d\n", value, *value);

    mp_exit_scope(pool);
}

int main() {
    mempool_t* pool = make_pool();
    mp_enter_scope(pool);

    printf("HI!\n");
    int *a = (int*) mp_malloc(pool, sizeof(int));
    *a = 5;
    printf("%p = %d\n", a, *a);

    int *b, *c, *d;

    {
        mp_enter_scope(pool);

        b = (int*) mp_malloc(pool, sizeof(int));
        c = (int*) mp_malloc(pool, sizeof(int));
        d = (int*) mp_malloc(pool, sizeof(int));

        *b = 114514;
        *c = 1919810;
        *d = 11111;

        printf("%p = %d\n", c, *c);

        fun_that_moves_value(pool, d);

        mp_borrow_out(pool, b);

        mp_exit_scope(pool);
    }

    printf("%p = %d\n", b, *b);

    mp_exit_scope(pool);
    destroy_pool(pool);
}
```

At the first line, we use `make_pool()` to create a memory pool. And we enter a **scope** in the second line. A **scope** is a part of code. Any memory allocated inside the scope using `mp_malloc` will be freed after exiting the scope. Now the scope looks like this:
```
 /
 |
 |
1|
 |
 |
 \
```
And then we allocated a block of memory and stored it to a. Because we used `mp_malloc` to allocate the memory, the pointer will also be stored in a memory pool belong to the current pool, which looks like:
```
 /
 |
 |
 |
1| a
 |
 |
 |
 \
```

And after that, we enter a new scope:
```
 /
 |     /
 |     |
 |     |
1| a  2|
 |     |
 |     |
 |     \
 \
```
And we allocated some blockes of memory and stored it into `b`, `c`, `d`.
```
 /
 |     /
 |     |
 |     | b
1| a  2| c
 |     | d
 |     |
 |     \
 \
```

The we called `fun_that_moves_value(pool, d)`. In the function, we create a new scope.
```
 /
 |     /     
 |     |     /
 |     | b   |
1| a  2| c  3|
 |     | d   |
 |     |     \
 |     \
 \
```
We didn't allocate anything, but we borrowed the `value` into the scope, and in this case, `d` has been borrowed in to the scope #3. Now `d` is no longer belong to #2, but #3.

```
 /
 |     /     
 |     |     /
 |     | b   |
1| a  2|    3| d
 |     | c   |
 |     |     \
 |     \
 \
```
So after exiting scope #3, `d` will be freed.
```
 /
 |     /     
 |     |        +========+
 |     | b      | R.I.P. |
1| a  2|        |   d    |
 |     | c      |        |
 |     |        +========+
 |     \
 \
 ```
And we used `mp_borrow_out`, which causes `b` belong to the scope #1 now. So after exit scope #2, `b` will not be freed.
```
 /
 |      
 |         +========+
 | b       | R.I.P. |
1|         |  d c   |
 | a       |        |
 |         +========+
 | 
 \
 ```

After doing this, we exited scope #1 so all the memories we allocated are freed. And after that, we destroyed the pool and exited the program.

## Build
```
cmake .
make
```
And copy out the `libcmemman.a` and all the files inside the directory `include/`.
> ### Note
> You can also compile the library by yourself or just copy all the sources into your project. In this case, you can enable the debug feature by defining the macro `__DEBUG__` while compiling the library so you can see when the scope exits and how many memories has been freed.

## Plans & Contribution
As you see, this library is highly incomplete. The library only has little features now but we hope it will be more and more powerful one day. So if you want to contribute this project, you can fork it and then make a pull request. We are looking forwards for your contributing.

> ### Note
> Before you contributing, please read the **[Contribution Guide](doc/ContributionGuide/Overview.md)** carefully, or your pull request may be rejected.

Here are a list of features that we are planning.

- [x] `mempool_t` & Scopes
- [ ] Long-Term Scopes (Which didn't store in a stack like ordinary scopes)
- [ ] Freeing
- [ ] Unsafe Methods (`mp_unsafe_remove_ptr()`, `mp_unsafe_add_ptr`, etc.)
- [ ] Auto destructure invoking when exiting scope.

## Documentation
[Click Here](doc/Overview.md)
