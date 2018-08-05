/* floats.c
 * --------
 * A program to explore the behavior of floating point types for lab.
 */

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


// Just a little helper to convert bool to string value when printing
static char *boolstr(bool b)
{
    return b ? "true" : "false";
}


/* Function: float_behavior
 * ------------------------
 * Tries various floating point operations and prints results so you can observe beahvior.
 */
static void float_behavior(void)
{
    printf("\nsizeof(float) = %zu  \nFLT_MIN = %g  FLT_MAX = %g  FLT_DIG = %d (num decimal digits)\n",
           sizeof(float), FLT_MIN, FLT_MAX, FLT_DIG);
    printf("\nsizeof(double) = %zu  \nDBL_MIN = %g  DBL_MAX = %g  DBL_DIG = %d\n\n",
          sizeof(double), DBL_MIN, DBL_MAX, DBL_DIG);

    printf("max * 2 = %g\n", DBL_MAX * 2);
    printf("1.0/0.0 = %g\n", 2.0/0.0);
    printf("0.0/0.4 = %g\n", 0.0/0.4);

    double infinity = 1.0/0.0;
    printf("\ninf * 2 = %g\n", infinity * 2);
    printf("inf - inf = %g\n", infinity - infinity);
    printf("Is inf == inf? %s\n", boolstr(infinity == infinity));
    printf("Is inf == -inf? %s\n", boolstr(infinity == -infinity));
    printf("Is inf > -inf? %s\n", boolstr(infinity > -infinity));
    printf("Is inf > DBL_MAX? %s \n", boolstr(infinity > DBL_MAX));

    double nan = 0.0/0.0;
    printf("\nnan * 2 = %g\n", nan * 2);
    printf("nan - nan = %g\n", nan - nan);
    printf("Is nan == nan? %s\n", boolstr(nan == nan));    
    printf("Is nan > nan? %s\n", boolstr(nan > nan));
    printf("Is nan < nan? %s\n", boolstr(nan < nan));
}


int main(int argc, char *argv[])
{
    float_behavior();
    return 0;
}

