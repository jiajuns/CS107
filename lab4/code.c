/* File: code.c
 * ------------
 * Code passages to read as part of lab.
 * Read lab4 writeup for more information.
 */
#include <stdio.h>
#include <string.h>


void *musl_memmove(void *dest, const void *src, size_t n)
{
    char *d = dest;
    const char *s = src;

    if (d==s) return d;
    if (s+n <= d || d+n <= s) return memcpy(d, s, n);

    if (d<s) {
        for (; n; n--) 
            *d++ = *s++;
    } else {
        while (n) {
            n--; 
            d[n] = s[n];
        }
    }
    return dest;
}


int main(int argc, char *argv[])
{
    musl_memmove(NULL, "cs107", 0);
    musl_memmove(NULL, "cs107", -1);
    return 0;
}
