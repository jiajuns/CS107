/* File: buggy.c
 * --------------
 * Intentionally buggy cdoe to observe under Valgrind.
 * Read lab3 writeup for more information.
 */

#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void make_error_1(const char *arg)
{
    printf("--- Making error 1: write past end of heap-allocated memory\n\n");
   
    char *ptr = malloc(8);
    printf("Copying string '%s' (%zu bytes total) to destination heap-allocated 8 bytes.\n", arg, strlen(arg) + 1);
    strcpy(ptr, arg);
    free(ptr);
}

void make_error_2(void)
{
    printf("--- Making error 2: access heap memory that has been freed\n\n");

    char *ptr = strdup("Jane Stanford");   // strdup does malloc+strcpy
    free(ptr);
    printf("Freed memory contains '%s'\n", ptr); // read from free memory
}

void make_error_3(void)
{
    printf("--- Making error 3: double free heap memory\n\n");

    char *ptr = strdup("David Starr Jordan");   // make heap copy
    char *another = ptr;    // second pointer to same location
    free(ptr);
    free(another);          // this location was already freed!
}

void make_error_4(void)
{
    printf("--- Making error 4: attempt to realloc non-heap address\n\n");
    char *str = "University";
    str = realloc(str, 20);
    free(str);
}

int main(int argc, char *argv[])
{
    int num = argc > 1 ? atoi(argv[1]) : 0;
    char *str =  argc > 2 ? argv[2] : "Stanford";

    switch(num) {
        case 1: make_error_1(str); break;
        case 2: make_error_2(); break;
        case 3: make_error_3(); break;
        case 4: make_error_4(); break;
        default: error(1, 0, "required argument is number 1, 2, 3, or 4");
    }
    return 0;
}
