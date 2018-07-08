#include "samples/prototypes.h"
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>

// ------- DO NOT EDIT ANY CODE IN THIS FILE (but do add comments!)  -------

int main(int argc, char *argv[])
{
    FILE *fp; // declare a FILE pointer

    if (argc == 1) {
        fp = stdin;
    } else {
        fp = fopen(argv[1], "r"); // assign fp pointer to the beginning of the file
        if (fp == NULL) error(1, errno, "cannot access '%s'", argv[1]);
    }

    char *line; // create a unassigned pointer to read line
    int n = 1;
    while ((line = read_line(fp)) != NULL) {
        if (*line != '\0') printf("%6d  %s", n++, line); // %6d reserve 6 chars space for integer
        printf("\n");
        free(line); // release the memory allocation in the heap for this line, 
    }
    fclose(fp);
    return 0;
}
