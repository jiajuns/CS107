#include "samples/prototypes.h"
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void print_last_n(FILE *fp, int n)
{
    char *line;
    char *arr[n]; // array with each element as a pointer to head of a string
    int i;

    //keep reading file until meet EOF
    for (i = 0; (line = read_line(fp)) != NULL; i++) {
        if (i >= n) free(arr[i % n]); // if i start to replace other element, release memory before
        arr[i % n] = line; // i mod n achieve circular buffer
    }

    int first = i % n; // first element index for output

    // print [    XXXXX] in the array
    if (i > n) { // the last line has replace some part of array
        for (int j = first; j < n; j++) {
            printf("%s\n", arr[j]);
            free(arr[j]);
        }
    }

    // print [XXXX     ] in array
    for (int k = 0; k < first; k++) {
        printf("%s\n", arr[k]);
        free(arr[k]);
    }
     
}

// ------- DO NOT EDIT ANY CODE BELOW THIS LINE (but do add comments!)  -------

int convert_arg(const char *str, int max)
{
    char *end;
    long n = strtol(str, &end, 10);
    if (*end != '\0') 
        error(1, 0, "Invalid number '%s'", str);
    if (n < 1 || n > max) 
        error(1, 0, "%s is not within the acceptable range [%d, %d]", str, 1, max);
    return n;
}

int main(int argc, char *argv[])
{
    int num = 10;

    if (argc > 1 && argv[1][0] == '-') {
        num = convert_arg(argv[1] + 1, 100000);
        argv++;
        argc--;
    }

    FILE *fp;
    if (argc == 1) {
        fp = stdin;
    } else {
        fp = fopen(argv[1], "r");
        if (fp == NULL) error(1, errno, "cannot access '%s'", argv[1]);
    }
    print_last_n(fp, num);
    fclose(fp);
    return 0;
}
