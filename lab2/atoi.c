/* File: atoi.c
 * ------------
 * Implementation of atoi for code study.
 * Read lab2 writeup for more information.
 */

#include <ctype.h>
#include <stdio.h>


int musl_atoi(const char *s)
{
    int n=0, neg=0;
    while (isspace(*s)) s++;
    switch (*s) {
        case '-': neg=1;
        case '+': s++;
    }
    /* Compute n as a negative number to avoid overflow on INT_MIN */
    while (isdigit(*s))
        n = 10*n - (*s++ - '0');
    return neg ? n : -n;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
        printf("musl_atoi(\"%s\") = %d\n", argv[i], musl_atoi(argv[i]));
    return 0;
}
