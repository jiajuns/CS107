/* File: parity.c
 * --------------
 * Read lab1 writeup for more information.
 */

#include <error.h>
#include <stdio.h>
#include <stdlib.h>


int compute_parity(int x)
{
    int result;

    while (x != 0) {
        result ^= (x & 1);  // invert result if lsb is on
        x = x >> 1;         // shift bits down
    }
    return result;
}


int main(int argc, char *argv[])
{
    if (argc < 2) error(1, 0, "missing argument");
    int val = atoi(argv[1]);
    printf("%d has %s parity\n", val, compute_parity(val) ? "odd" : "even");   
    return 0;
}
