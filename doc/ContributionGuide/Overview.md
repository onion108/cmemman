# CMemMan Documentation for Contributors

## Overview

The documentation is about how to contribute to the libcmemman project.

## Chapters
**[1 Build](#11-build)**
[1.1 Development Environment](#11-development-environment)
[1.2 Testing](#12-testing)
**[2 Adding Contents](#2-adding-contents)**
[2.1 Adding Types](#21-adding-types)
[2.2 Adding Associated Methods](#22-adding-associated-methods)
**[3 Naming](#3-naming)**
[3.1 Methods (Functions), Variables and Fields](#31-methods-functions-variables-and-fields)
[3.2 Types](#32-types)
[3.3 Associated Methods](#33-associated-methods)
**[4 Documentation](#4-documentation)**
[4.1 Documentation for Types](#41-documentation-for-types)
[4.2 Documentation for Associated Methods](#42-documetnation-for-associated-methods)
**[5 `git commit` Messages](#5-git-commit-messages)**

## 1 Build

### 1.1 Development Environment

To build the project for contribution, you need the following tools:
```
cmake
g++ (or clang, msvc[unsupported])
make
```

For editors, you can choose what you want, but I recommend to use `helix` or `vscode` as your editor.
### 1.2 Testing
To test the library, you can create a directory called `test` in the project directory. It has been added into the `.gitignore` so it will be ignored by `git`. Inside the `test`, you need to create two files. `main.c` for testing the lib, and `Makefile` to build the test executable. The contents of `Makefile` are showed down here:
```makefile
.PHONY:all
all:
    g++ -xc -O2 -Wall -std=c17 -o test -- main.c ../src/*.c
.PHONY:debug
debug:
    g++ -xc -O2 -Wall -std=c17 -o test -g -D__DEBUG__ -- main.c ../src/*.c
```
## 2 Adding Contents

### 2.1 Adding Types
Please add types into a seprated file. Create header files in the `include/` directory and implementations in the `src/` directory. After that, please write a documentation of it. 

### 2.2 Adding Associated Methods
**Associated Methods** are methods that associated to some objects. The first argument must be `xxx_t *self`. The associated methods should be in one file with the type.

## 3 Naming

### 3.1 Methods (Functions), Variables and Fields
They should be named in `snake_case`. For example:
```C
a_method(); // Correct
aMethod(); // Incorrect

int my_counter = 0; // Correct
int myCounter = 0; // Incorrect

typedef struct _my_type_t {
    int a_field; // Correct
    int aField; // Incorrect
} my_type_t;
```

### 3.2 Types
Types should be named in `snake_case` and ends with `_t`. Also you must use `typedef` to make the type name shorter and easy to read. For example:
```C
typedef struct _my_type_t {} my_type_t; // Correct
typedef struct {} my_type_t; // Also Correct
struct my_type_t {}; // Incorrect, user have to use 'struct my_type_t' instead of 'my_type_t'.
typedef struct {} MyType; // Incorrect
typedef struct {} my_type; // Incorrect
```

### 3.3 Associated Methods
You should name associated methods in `snake_case`. The name of the function must starts with the type name without suffix `_t` or the short presentation of the type name. For example:
```C
// Recommended to define this macro in order to make code shorter.
#define SELF my_type_t *self

void my_type_some_method(SELF); // Correct
void mt_some_method(SELF); // Also Correct
void some_method(SELF); // Incorrect
void SomeMethodOfMyType(SELF); // Incorrect
void my_type_t_some_method(SELF); // Incorrect

```

Private associated methods (methods that only appears in the implementation file) should be named like an associated method and add `prv_` in front of the name.

For constructors and destructors, they should be named in the format of `make_xxx`, `make_xxx_with_xxx` (for constructors) and `destroy_xxx` (for destructors).

## 4 Documentation

### 4.1 Documentation for types
To add a documentation for a type, first you should create a new directory in the `doc/` directory with a short name for the type in `BigPascalCase`. Create a markdown file in this directory and name it as the `${DirectoryName}.md` (where `${DirectoryName}` is the name of the directory you just created). This markdown file is called the **Entry Documentation**. And then add the link to the main documentation of your type to the `doc/Overview.md`. The link should be in the section *Structures*. And then, fill in the main documentation with the following template.
```markdown
[< Overview](../Overview.md)

## `your_type_t`

### Definition
Copy the definition of your type here.
### Members
Explain members in your type.
### Associated Methods
The format of this section should be similar to doc/MemoryPool/MemoryPool.md .
#### Constructors and Destructors
Put links to the documentations of the constructors and destructors here, with the prototype.
#### Subject 1
Put some associated methods here
#### Subject 2
Put some associated methods here
...
#### Subject n
Put some associated methods here

```

### 4.2 Documetnation for Associated Methods
The format of it should be similar to `doc/MemoryPool/mp_borrow_out.md`.

## 5 `git commit` messages
The commit messages should also follow some rules. Here are some types of commit messages.
```
fix: (description here)
```
Messages start with `fix` means the current commitment is about fixing some bugs.
```
feat: (description here)
```
Messages start with `feat` means the current commitment is about adding a new feature.
```
chore: (description here)
```
Messages start with `chore:` means the current commitment is about doing something others, e.g., editing `README.md`, adding documentations, editing `CMakeList.txt`, etc.
