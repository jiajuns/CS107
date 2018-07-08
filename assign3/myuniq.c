#include "samples/prototypes.h"
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// initial estimate of number of uniq lines
// resize-as-you-go, add in increments of 100
#define ESTIMATE 100

struct sline {
    int count;
    char *text; 
};

void print_uniq_lines(FILE *fp)
{
    int found;
    int i = 0;
    struct sline *arr = malloc(ESTIMATE * sizeof(struct sline));
    char *line;


    while ((line = read_line(fp)) != NULL)
    {
        if ((i != 0) && ((i % ESTIMATE) == 0))
        {
            arr = realloc(arr, ((i/ESTIMATE)+1)*ESTIMATE*sizeof(struct sline));
        }

        found = 0;
        for (int j = 0; j < i; j++)
        {
            if (strcmp(arr[j].text, line) == 0)
            {
                arr[j].count += 1;
                found = 1;
                break;
            }
        }

        if (found == 0)
        {
            arr[i].count = 1;
            arr[i].text = line;
            i++;
        }

        // print arr
        for (int k=0; k<i; k++)
        {
            printf("%6d %s\n", arr[k].count, arr[k].text);
        }
    }

    free(arr);
}


// ------- DO NOT EDIT ANY CODE BELOW THIS LINE (but do add comments!)  -------

int main(int argc, char *argv[])
{
    FILE *fp;

    if (argc == 1) {
        fp = stdin;
    } else {
        fp = fopen(argv[1], "r");
        if (fp == NULL) error(1, errno, "cannot access '%s'", argv[1]);
    }
    print_uniq_lines(fp);
    fclose(fp);
    return 0;
}
