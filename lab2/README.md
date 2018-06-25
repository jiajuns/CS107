# Lab2

## atoi
atoi function converts a string argument to an integer. The main function will pass argument as a pointer to the atoi function. atoi function skipped any space and first identify any positive or negative sign. Then loop through all the digits of the string until hit an not string character.

## buggy
The exercises for buggy is to first practice ability to using `gdb` and `valgrind`; secondly, understand some common bugs that can happen in c programming.

```c
char *uninitialized_ptr;
printf("strlen(uninitialized_ptr) = %zu\n", strlen(uninitialized_ptr));
```
The first bug caused by using unintialized pointers. The usage of an uninitialized pointer typically results in program crashes if the pointer accesses memory it is not allowed to.

The second bug caused by null-terminators error. When initializing string without providing a string or dose not give a terminator `'\0'`.

The third bug is caused by strcpy called on dst that is too small. The string requires `n+1` bits to store a string.

## 
