/* File: round.c
 * -------------
 * Code passages to read as part of lab1.
 */

#include <stdbool.h>
#include <stdio.h>

bool is_power_of_2(unsigned int x)
{
    return (x & (x -1)) == 0;   // from lecture
}

// What is special about powers of 2 that allow rounding via bitwise ops
// in place of the more expensive multiply/divide used for general case?
unsigned int round_up(unsigned int val, unsigned int mult)
{
    if (is_power_of_2(mult))
        return  (val + mult-1) & ~(mult-1);
    else
        return ((val + mult-1) / mult) * mult;
}

void try_round(unsigned int v, unsigned int m)
{
    printf("round_up(%u, %u) = %u\n", v, m, round_up(v, m));
}

int main(int argc, char *argv[])
{
    try_round(2, 7);
    try_round(6, 5);
    try_round(100, 32);
    try_round(4, 4);
    return 0;
}

