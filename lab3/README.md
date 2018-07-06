# Lab3

## code.c

1. when stepping through the code under gdb and use `info locals`, you can see the status of local varible. It is interesting to find that when variables are not initialized, their values are random.
2. The last two command return different value:
    ```c
    p sizeof(arr);
    p sizeof(ptr);

    p arr = arr + 1;
    p ptr = ptr + 1;
    ```
    First of all array name is `constant` in that it cannot be assigned to. 

    Secondly, array is not a pointer but they are closely related. whenever an array appears in an expression, the compiler implicitly generates a pointer to the array's first element, just as if the programmer had written &a[0]. (The exceptions are when the array is the operand of a sizeof or & operator, or is a string literal initializer for a character array

3. When passing array to a function, only name of the array is passed (i.e. starting address of memory area is passed as argument).

4. It is worth pointing out that:
    ```c
    *s = 'j';
    s = "Leland";
    ```
    The first line is change the first string of where the pointer pointing to `j`; while the second line knows to assign the address where `Leland` stores to the pointer `s`.

## heap.c

### substract
1. `char *strstr(const char *haystack, const char *needle)` function finds the first occurence of the substring `needle` in the string `haystack`. The function returns a pointer where the first occurence in haystack of any of the entire sequence of characters specified in needle, or a null pointer if the sequence is not presented in `haystack`.
2. `strdup` is to duplicate the constant string, which will heap allocates a string and return it to `main`
3. substract two pointers gives a length between the location of two pointers.
4. The result dose not have null terminator.
5. `strcat(result, found+nremoved)` works relies on the fact that line 9 returns `result` dose not has null terminator.

### join
1. size argument to `realloc` is the total number of bytes including any previously allocated part.
2. The realloc man page says the return value from realloc(ptr, newsize) may be the same as ptr, but also may be different. Therefore, catch the return value of `realloc` is super important.

## calloc
