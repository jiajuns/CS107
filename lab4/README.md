# lab4


## callbacks

1. The advantage of doing this upfront is that it provides generic interface and by dereferencing to a value and store it locally inside a function, it preserve the original value of the arguments.

2. To sort in reverse order, you can add a negative sign to the callback function. In order to compare by one field as a primary sort and break ties by comparing a secondary field, can wrap two callbacks function in a new function and passing the new callback function to `qsort`

3. The function can work but it will decode the bytes information in a wrong way and produce strange result.

4. A big difference between `letter_cmpfn` and `string_cmpfn` is one assume the argument is a pointer to a pointer.


## gfind_max

1. typecast `(char *)` will make sure the pointer moves in increments of 1 at a time. 
    ```c
    void *ith = (char *)arr + i*elemsz;
    ```

2. declare compar as pointer to function (pointer to const void, pointer to const void) returning int
    ```c
    int (*compar)(const void *, const void *)
    ```
3. when passing wrong number of arguments to the function, it will arise error during compiling. If the datatype of the argument is wrong, it will only show warning message, the program can still run.

4. returning pointer to a value rather than the value itself can make the `gfind_max` function more generic. Since the `gfind_max` dose not know the datatype it handles, it cannot cast the pointer to a value correctly.

5. the clinet can repack the `compar` function and add a negative sign inside the repacked function

6. there is no compile error or runtime error because those function dose not care the input argument type. It treats all argument as `void *`. Even `valgrind` dose not show any error.

7. the error is due to wrong variable bytes size. the error the max value comes from read memory stack at 1 increment. This result unpredicted value from memory bytes.

8. it compares pointer itself, the last element has the largest pointer value.

9. program crashes at `cmp_first_char` function.

10. The reason for creating this hack is due to `bsearch` functions requires `key` and `words` have same variable type. Before the fix, `key` is a pointer to `char` and `words[0]` is a pointer that pointing to another pointer. 


## memmove

1. internally it manipulates the pointer as `char` because it can move 1 byte at a time and use 1 byte as a basic unit.

2. it handles two pointer pointing to the same location.

3. it handles the case when `src` and `dest` dose not overlap with each other. According to `memcpy` documentation:
    
    The behavior is undefined if access occurs beyond the end of the dest array. If the objects overlap (which is a violation of the restrict contract) (since C99), the behavior is undefined.

4. `if/else` deals with `src` and `dest` overlapping with each other. One is `src` in front of `dest` and the other is `dest` in the front. Both of them cannot be dealt with `memcpy`.

5. `musl_memmove(NULL, "cs107", 0)` dose not crash because `memcpy` dose not actually do any copy. 