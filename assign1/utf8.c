#include "samples/prototypes.h"
#include <error.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>



int to_utf8(unsigned short cp, unsigned char seq[])
{
    // determine num of sigbits in cp, thus decides num of bytes
    // fill bits into bytes, then feed in seq[]
    if (cp >> 7 == 0) {
        seq[0] = cp;
        return 1;
    } else if (cp >> 11 ==0){
        seq[0] = (1 << 7) + (1 << 6) + (cp >> 6);
        seq[1] = (1 << 7) + (cp & 0x3f);
        return 2;
    } else {
        seq[0] = 0xe0 + (cp >> 12);
        seq[1] = (1 << 7) + ((cp >> 6) & 0x3f);
        seq[2] = (1 << 7) + (cp & 0x3f);
        return 3;
    }
}




// ------- DO NOT EDIT ANY CODE BELOW THIS LINE (but do add comments!)  -------

void print_utf8(unsigned short cp, unsigned char seq[], int len)
{
    int i;
    printf("U+%04X   Hex:", cp);
    for (i = 0; i < len; i++)
       printf(" %02x", seq[i]);
    for ( ; i < 4; i++) printf("   ");
    seq[len] = '\0';
    printf("Character: %s  \n", seq);  
}

unsigned short convert_arg(const char *str, unsigned short low, unsigned short high)
{
    char *end;
    long n = strtol(str, &end, 0);
    if (*end != '\0')
        error(1, 0, "Invalid code point '%s'", str);
    if (n < low || n > high) 
        error(1, 0, "Code point %s not in range [%u, %u]", str, low, high);
    return n;
}

int main(int argc, char *argv[])
{
    if (argc < 2) 
        error(1, 0, "Missing argument. Please supply one or more unicode code points in decimal or hex.");
    
    for (int i = 1; i < argc; i++) {
        unsigned short cp = convert_arg(argv[i], 0, USHRT_MAX);
        unsigned char seq[4];
        int len = to_utf8(cp, seq);
        print_utf8(cp, seq, len);  
    }
    return 0;
}
