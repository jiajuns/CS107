/* File: challenge.c
 * -----------------
 * This is for the lab1 challenge problem
 */

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

bool has_zero_byte(unsigned long val)
{
    unsigned long ones = ~0UL/UCHAR_MAX;
    unsigned long highs = ones << (CHAR_BIT - 1);
    return (((val - ones) & highs) & ~val) != 0;
}


int main(int argc, char *argv[])
{
    unsigned long num = 0x1a2b3c004d5e6f;
    printf("has_zero_byte(%#lx) = %d\n", num, has_zero_byte(num));
    return 0;
}

