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
    char *rp = malloc(MINIMUM_SIZE);
    int i = 0;
    int length = 1;

    while (1)
    {
        i++;   
        rp = realloc(rp, i*MINIMUM_SIZE);
        rp = fgets(rp, i*MINIMUM_SIZE, fp);
        if (rp == NULL) return NULL;  // case 5
        length = strlen(rp);
        if (rp[length - 1] == '\n') break;
    }
    
    // replace '\n' at the end with '\0'
    if (rp[length - 1] == '\n') { // case 4
        rp[length - 1] = '\0';
    }
    return rp;
}

//case 1. XXXXX\n (<32 length)
//case 2. XXXXXXXXXXXXXXXXXXXXXXXXXXXX\n (> 32 length)
//case 3. \n
//case 4. XXXXXXXXXXXXXXXXXXXXXEOF (>32)
//case 5. EOF
//case 6. XXXXXXX\nEOF

