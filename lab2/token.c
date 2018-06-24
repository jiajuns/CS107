/* File: token.c
 * -------------
 * Implementation of strtok for code study.
 * Read lab2 writeup for more information.
 */

#include <stdio.h>
#include <string.h>

char *musl_strtok(char *s, const char *sep)
{
    static char *p = NULL;

    if (s == NULL && ((s = p) == NULL))
        return NULL;
    s += strspn(s, sep);
    if (!*s) 
        return p = NULL;
    p = s + strcspn(s, sep);
    if (*p) 
        *p++ = '\0';
    else 
        p = NULL;
    return s;
}

void token_loop(char *input, const char *delims)
{
    char *token = musl_strtok(input, delims);
    while (token != NULL) {
        printf("%s\n", token);
        token = musl_strtok(NULL, delims);
    }
    printf("\n");
}


int main(int argc, char *argv[])
{
    char *str = "red-green-blue";
    char *first;
    char copy[100];
    strcpy(copy, str);

    //first = musl_strtok(str, "-");   // attempt to tokenize string constant fails at runtime. Why?
    first = musl_strtok(copy, "-");  // but ok to tokenize copy. Why? What's different?
    printf("First token is %s\n", first);

    return 0;
}
