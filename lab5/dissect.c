/* dissect.c
 * ---------
 * A program to report on the underlying representation of various float values.
 */

#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void print_float_internals(float f, const char *name, const char *comment)
{
    unsigned int bits = *(unsigned int *)&f; // trick compiler into giving us access to raw bits
    printf(" %c ", signbit(f) ? '-' : '+'); // msb is sign bit
    int biased_e = (bits >> 23) & 0xff; // 8 exp bits (biased)
    printf("%s.", biased_e == 0 || biased_e == 255? "   " : "(1)");
    for (int i = 22; i >= 0; i--)        // low 23 bits are significand
        printf("%d", (bits >> i) & 1); 
    printf(" * 2^%-4d ", biased_e == 0 ? -126 : biased_e - 127);
    printf(" %s ", name);
    if (!comment) printf("(value represented = %.9g)\n", f);
    else printf("(%s)\n", comment);
}


/* Function: float_bits
 * --------------------
 * Prints internal representation for various float values.
 */
static void float_bits(void)
{
    unsigned int rawbits = 1;
    float f = *(float *)&rawbits;

    printf("\nSome various float values and their representation:\n");
    print_float_internals(0, "Zero", NULL);
    print_float_internals(FLT_MIN, "FLT_MIN, smallest normalized float", NULL);
    print_float_internals(FLT_MAX, "FLT_MAX", NULL);
    print_float_internals(f, "smallest float, denormalized", NULL);
    print_float_internals(1.0/0.0, "Infinity", NULL);
    print_float_internals(0.0/0.0, "nan", NULL);
    print_float_internals(1.0, "1.0", NULL);
    print_float_internals(1.5, "1.5", "how did float bits change from 1.0 to 1.5?");
    print_float_internals(1.25, "1.25", "how did float bits change from 1.5 to 1.25?");
    print_float_internals(-1.25, "-1.25", "how did negation change float bits?");
    print_float_internals(127.25, "127.25", "note bit pattern for integer 127 appears within float bits!");
    print_float_internals(126.25, "126.25", "how did subtract 1 change float bits?");
    print_float_internals(63.125, "63.125", "how did divide by 2 change float bits?");
    print_float_internals(M_PI, "M_PI", "non-terminating binary fraction");
    print_float_internals(1.0/3, "1/3", "also non-terminating");
    print_float_internals(.1, "0.1", "also non-terminating");
}

// parse simple binary float expression
// Code is not aiming to be robust/general, just something quick & dirty
// that lets you play with floats in lab
static bool parse_float_expression(char *line, float *fp)
{
    float op1, op2;

    line[strlen(line)-1] = '\0'; // remove trailing newline
    char *end;
    op1 = strtof(line, &end);
    char *oper = strpbrk(end, "+-*/");
    if (*end == '\0' || !oper) {
        *fp = op1;
        return true;
    }
    op2 = strtof(oper+1, &end);
    switch (*oper) {
        case '+': *fp = op1 + op2; break;
        case '-': *fp = op1 - op2; break;
        case '*': *fp = op1 * op2; break;
        case '/': *fp = op1 / op2; break;
    }
    return true;
}

static void interactive(void)
{
    printf("\nNow try your own values to see how they are represented as float.\n");
    printf("Enter a single float value or a binary arithmetic expression.\n");

    while (1) {
        char line[32];
        float f;

        printf("\nEnter a float expression (control-d to quit): ");
        if (!fgets(line, sizeof(line), stdin)) break;
        if (parse_float_expression(line, &f))
            print_float_internals(f, line, NULL);
    }
}

int main(int argc, char *argv[])
{
    float_bits();
    interactive();
    return 0;
}
