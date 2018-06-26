#include "samples/prototypes.h"
#include <string.h>


const char *get_env_value(const char *envp[], const char *key)
{
    // int n = strlen(key);
    char target[strlen(key)+1];   // array to hold the result.
    strcpy(target, key);
    strcat(target, "=");
    int n = strlen(target);
    for (int i = 0; envp[i] != NULL; i++) {
        if ((strncmp(envp[i], target, n) == 0)) {
            return strchr(envp[i], '=') + 1;
        }
    }
    return NULL;
}


bool scan_token(const char **p_input, const char *delimiters, char buf[], size_t buflen)
{   
    if (!**p_input) return false;
    // use strspn find the index 'start' of first non-delim/valid char
    int start = strspn(*p_input, delimiters);
    // move p_input to fist valid char
    *p_input += start;
    // if no valid char, return false
    if (!**p_input) return false;
    // use strcspn find the index 'end' of the next delim
    int end = strcspn(*p_input, delimiters);
    // determine the num of chars to write in buf
    int n = (end > buflen - 1) ? (buflen - 1) : end;
    // for n loop, write one char at **p_input, move *p_input forward by 1
    for (int i = 0; i < n; i++) {
        buf[i] = **p_input;
        *p_input += 1;
    }
    // add null terminator at the end of buffer
    buf[n] = '\0'; 
    return true;
}
