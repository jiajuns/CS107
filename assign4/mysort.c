#include "samples/prototypes.h"
#include <error.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LEN 4096
#define MIN_NLINES 100

typedef int (*cmp_fn_t)(const void *, const void *);

int cmp_pstr(const void *p1, const void *p2)
{   
    return strcmp(*(const char **)p1, *(const char **)p2);
}

int cmp_pstr_len(const void *p1, const void *p2)
{
    return strlen(*(const char **)p1) - strlen(*(const char **)p2);
}

int cmp_pstr_numeric(const void *p1, const void *p2)
{
    return atoi(*(const char **)p1) - atoi(*(const char **)p2); 
}

void sort_lines(FILE *fp, cmp_fn_t cmp, bool uniq, bool reverse)
{   
    char *line = malloc(MAX_LINE_LEN * sizeof(char));
    char **arr = malloc(MAX_LINE_LEN * sizeof(char *));
    char *dupline;
    
    size_t length = 0;
    size_t limit = MIN_NLINES;
    while ((line = fgets(line, MAX_LINE_LEN, fp)) != NULL)
    {
        dupline = strdup(line);
        if (uniq)
        {
            binsert(&dupline, arr, &length, sizeof(char *), cmp);
        } else {
            arr[length] = dupline;
            length += 1;
        }

        if (length >= limit)
        {
            limit *= 2;
            arr = realloc(arr, limit*sizeof(char *));
        }
    }

    if (!uniq)
    {
        qsort(arr, length, sizeof(char *), cmp);
    }

    if (!reverse)
    {
        for (int i=0; i<length; i++)
        {
            printf("%s", arr[i]);
        }
    } else {
        for (int i=length-1; i>=0; i--)
        {
            printf("%s", arr[i]);
        }
    }
    free(arr);
    free(line);
}

int main(int argc, char *argv[])
{
    cmp_fn_t cmp = cmp_pstr;
    bool uniq = false, reverse = false;

    int opt;
    while ((opt = getopt(argc, argv, "lnru")) != -1) {
        switch (opt) {
            case 'l': cmp = cmp_pstr_len; break;
            case 'n': cmp = cmp_pstr_numeric; break;
            case 'r': reverse = true; break;
            case 'u': uniq = true; break;
            default: return 1;
        }
    }

    FILE *fp = stdin;
    if (optind < argc) {
        fp = fopen(argv[optind], "r");
        if (fp == NULL) error(1, 0, "%s: no such file", argv[optind]);
    }
    sort_lines(fp, cmp, uniq, reverse);
    fclose(fp);
    return 0;
}
