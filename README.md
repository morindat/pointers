# Pointers

Personal notes and examples while learning pointers properly in C and C++.

The goal of this repository is to build a clear mental model of addresses,
indirection, memory layout, pointer arithmetic, ownership, and the common bugs
that come from using pointers incorrectly.

## Build And Run

Compile a C file:

```sh
gcc -Wall -Wextra -pedantic -std=c11 basic.c -o basic
./basic
```

Compile the pointer types example:

```sh
gcc -Wall -Wextra -pedantic -std=c11 pointer_types.c -o pointer_types
./pointer_types
```
Also

```sh
gcc -Wall -Wextra -g -fsanitize=address,undefined -o prog pointer_types.c && ./prog
```

Compile a C++ file when C++ examples are added:

```sh
g++ -Wall -Wextra -pedantic -std=c++20 example.cpp -o example
./example
```

## Learning Roadmap

1. Addresses, `&`, and `*`
2. Pointer types and dereferencing
3. Pointer arithmetic and arrays
4. `const` with pointers
5. `void*` and casts
6. Stack vs heap memory
7. `malloc`, `calloc`, `realloc`, and `free`
8. Dangling, null, wild, and uninitialized pointers
9. Function pointers
10. Pointers to pointers
11. C strings and buffer safety
12. Structs, pointers to structs, and linked lists
13. C++ references vs pointers
14. C++ `new`/`delete` and RAII
15. Smart pointers: `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`

## Notes To Keep

For each topic, try to document:

- What the pointer stores
- What memory it points to
- Who owns that memory
- How long the pointed-to memory is valid
- What can go wrong
- A small program that proves the concept

## Debugging Tools

Useful tools while learning:

```sh
gcc -Wall -Wextra -g file.c -o file
gdb ./file
```

```sh
gcc -Wall -Wextra -g -fsanitize=address,undefined file.c -o file
./file
```

AddressSanitizer and UndefinedBehaviorSanitizer are especially useful for
catching invalid memory access, use-after-free, and undefined behavior.
