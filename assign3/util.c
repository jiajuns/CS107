#include "samples/prototypes.h"
#include <stdlib.h>
#include <string.h>

// initial allocation will be for min size, if not big enough, doubles
// to 64, then 128, then 256, etc. as needed to accommodate the entire line
// resize-as-you-go, doubling each time
#define MINIMUM_SIZE 32


char *read_line(FILE *fp)
{
    // allocate minimum size of bytes for a pointers
    char *rp = calloc(MINIMUM_SIZE, 1);
    char *buf = malloc(MINIMUM_SIZE);
    int i = 1;
    int length;

    while (1)
    {
        rp = realloc(rp, i*MINIMUM_SIZE);
        buf = fgets(buf, MINIMUM_SIZE, fp);
        if (buf == NULL) return NULL;  // case 5
        strcat(rp, buf);
        length = strlen(rp);
        if (rp[length - 1] == '\n') 
        {
            rp[length - 1] = '\0';
            break;
        }
        i++;
    }
    
    return rp;
}

//case 1. XXXXX\n (<32 length)
//case 2. XXXXXXXXXXXXXXXXXXXXXXXXXXXX\n (> 32 length)
//case 3. \n
//case 4. XXXXXXXXXXXXXXXXXXXXXEOF (>32)
//case 5. EOF
//case 6. XXXXXXX\nEOF