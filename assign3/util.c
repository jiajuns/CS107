#include "samples/prototypes.h"
#include <stdlib.h>
#include <string.h>

// initial allocation will be for min size, if not big enough, doubles
// to 64, then 128, then 256, etc. as needed to accommodate the entire line
// resize-as-you-go, doubling each time
#define MINIMUM_SIZE 32


char *read_line(FILE *fp)
{
    char *res = calloc(MINIMUM_SIZE, 1); // initialize memory with all 0
    char *buf = malloc(MINIMUM_SIZE); // reserve memory but not initialize

    // loop until res ends with '\n'
    for (int i = 0; res[strlen(res) - 1] != '\n'; i++) { // case1,3
        if (i > 0) { // allocate more memory for res
            res = realloc(res, MINIMUM_SIZE * (i+1)); // case 2
        }
        buf = fgets(buf, MINIMUM_SIZE, fp);
        // if fgets return NULL, it meets EOF or other errors
        if (buf == NULL) return NULL; // case 5
        // concat fixed sized(32) buf to res
        strcat(res, buf);      
    }
    
    free(buf);

    // replace '\n' at the end with '\0'
    if (res[strlen(res) - 1] == '\n') { // case 4
        res[strlen(res) - 1] = '\0';
    }
    return res;
}
//case 1. XXXXX\n (<32 length)
//case 2. XXXXXXXXXXXXXXXXXXXXXXXXXXXX\n (> 32 length)
//case 3. \n
//case 4. XXXXXXXXXXXXXXXXXXXXXEOF (>32)
//case 5. EOF
//case 6. XXXXXXX\nEOF

