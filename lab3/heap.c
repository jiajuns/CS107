/* File: heap.c
 * ------------
 * Code passages to read as part of lab.
 * Read lab3 writeup for more information.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *subtract(const char *outer, const char *inner)
{
    char *found = strstr(outer, inner);

    if (!found) return strdup(outer);
    int nbefore = found - outer;
    int nremoved = strlen(inner);
    char *result = malloc(strlen(outer) + 1 - nremoved);
    strncpy(result, outer, nbefore);
    strcpy(result + nbefore, found + nremoved);
    return result;
}

char *join(char *arr[], int n)
{
    char *result = strdup(arr[0]);

    for (int i = 1; i < n; i++) {
        result = realloc(result, strlen(result) + strlen(arr[i]) + 1);
        strcat(result, arr[i]);
    }
    return result;
}

void *musl_calloc(size_t nelems, size_t elemsz)
{
    if (nelems && elemsz > SIZE_MAX/nelems) {
        return NULL;
    }
    size_t total = nelems * elemsz;
    void *p = malloc(total);
    if (p != NULL) {
        long *wp;
        size_t nw = (total + sizeof(*wp) - 1)/sizeof(*wp);
        for (wp = p; nw != 0; nw--,wp++) 
            *wp = 0;
    }
    return p;
}

int main(int argc, char *argv[])
{
    char *without = subtract("centimeter", "time");
    printf("%s\n", without);
    free(without);

    if (argc > 1) {
        char *joined = join(argv + 1, argc - 1);
        printf("%s\n", joined);
        free(joined);
    }
    return 0;
}
