/* code.c
 * ------
 * Code study examples from lab. Refer to lab writeup for more information.
 */

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

double musl_fmax(double x, double y)
{
    if (isnan(x))
        return y;
    if (isnan(y))
        return x;
    /* handle signed zeros, see C99 Annex F.9.9.2 */
    if (signbit(x) != signbit(y))
        return signbit(x) ? y : x;
    return x < y ? y : x;
}

// NOTE: both hypot ignore exceptional inputs as simplification

double naive_hypot(double x, double y)
{
    return sqrt(x*x + y*y);
}

double better_hypot(double x, double y)
{
    x = fabs(x);
    y = fabs(y);
    double max = fmax(x, y);
    double min = fmin(x, y);
    double r = min / max;
    return max*sqrt(1 + r*r);
}

int main(int argc, char *argv[])
{
    float posNan = copysign(nan(""), 1);
    float negNan = copysign(nan(""), -1);

    printf("musl_fmax = %g\n", musl_fmax(INFINITY, DBL_MAX));
    printf("naive_hypot = %g\n", naive_hypot(3, 4));
    printf("better_hypot = %g\n", better_hypot(3, 4));
    return 0;
}