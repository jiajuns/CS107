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