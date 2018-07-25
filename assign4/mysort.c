#include "samples/prototypes.h"
#include <error.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LEN 4096
#define MIN_NLINES 100

typedef int (*cmp_fn_t)(const void *p, const void *q);

int cmp_pstr(const void *p, const void *q)
{
    return strcmp(*(const char **)p, *(const char **)q);
}

int cmp_pstr_len(const void *p, const void *q)
{
    return strlen(*(const char **)p) - strlen(*(const char **)q);
}

int cmp_pstr_numeric(const void *p, const void *q)
{
    return atoi(*(const char **)p) - atoi(*(const char **)q);
}

void sort_lines(FILE *fp, cmp_fn_t cmp, bool uniq, bool reverse)
{
    // create an array of string in heap for lines with MIN_NLINES
    char **arr = malloc(MIN_NLINES * sizeof(char *));
    char *line = malloc(MAX_LINE_LEN);
    char *dupline = malloc(MAX_LINE_LEN);
    size_t len = 0;
    size_t limit = MIN_NLINES;
    // use fgets to read a line with MAX_LINE_LEN, then strdup to store into heap
    while ((line = fgets(line, MAX_LINE_LEN, fp)) != NULL) {
        if (len >= limit) {
            limit *= 2;
            arr = realloc(arr, limit * sizeof(char *));
        }
        dupline = strdup(line);
        if (uniq) {
            binsert(&dupline, arr, &len, sizeof(*arr), cmp);
        } else {
            arr[len] = dupline;
            len++;
        }
    }
    // if not uniq, use qsort to sort array
    if (!uniq) {
        qsort(arr, len, sizeof(*arr), (int (*)(const void *, const void *))cmp);
    }

    // print based on reverse or not
    if (!reverse) {
        for (int i = 0; i < len; i++) {
            printf("%s", arr[i]);
        }
    } else {
        for (int i = len - 1; i >= 0; i-- ) {
            printf("%s", arr[i]);
        }
    }
    free(arr);
    free(line);
    free(dupline);
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
