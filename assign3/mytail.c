#include "samples/prototypes.h"
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void print_last_n(FILE *fp, int n)
{
    char *line;
    char *arr[n];
    int i = 0;
    while ((line = read_line(fp)) != NULL)
    {
        // if (i >= n) free(arr[i % n]);
        arr[i % n] = line;
        i++;
    }
    int idx = i % n;
    if (i > n)
    {   
        // print out the last part of the array first
        for (int j = idx; j < n; j++)
        {
            printf("%s\n", arr[j]);
        }
    }

    for (int j = 0; j < idx; j++)
    {
        printf("%s\n", arr[j]);
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
