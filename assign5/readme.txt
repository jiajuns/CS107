File: readme.txt
Author: Wenjie Hu
----------------------

1) Exploring the real world

1a) Python:
 - by running sys.float_info, the maximum float value is 1.7976931348623157e+308, the minimum float value is 2.2250738585072014e-308, which is the same as DBL_MAX and DBL_MIN in C.
 - 1.7976931348623157e+308 * 2 = inf
 - the smallest precision epsilon=2.220446049250313e-16
 - 1.0/0.0 gives ZeroDivisionError: float division by zero
 - inf - inf = nan
Conclusion: Python uses the same IEEE float point, but only uses 64-bit double precision. It has more restriction on the use of float, such as raisng error for dividing by 0.

1b) R:
 - .Machine$double.xmax = 1.797693e+308, .Machine$double.xmin = 2.225074e-308, .Machine$double.eps = 2.220446e-16
- 1.797693e+308 * 2 = inf
- 1.0/0.0 = Inf
- Inf - Inf = NaN
Conclusion: R follows the similar behaviors as Python, thus it also uses the same IEEE float point with 64-bit double precision. The difference with Python is that it allows Inf by divisoin of 0 but not raise error.

2) Floating average

2a) averageA:
 - method: this functions divide each value in the float array by the size of array, and then sum them up.
 - strengths: It will avoid the issue of float overflow when taking sum of each value directly, because some intermediate sum might go beyond the range of FLT_MAX and become inf, thus never recover back.
 - vulnerabilities: the division of each value might get the result with different rounding precision, thus have bias in the average results, especially when the array size is large, or the values are very small, or the magnitudes of values in the array vary a lot.

 2b) averageB:
 - method: sort the array in acsending order, and then sum them up one by one, finally divided by the array size.
 - strengths: in each iteration it adds the value with close magnitude of previous values, thus it reduce the rounding error in addition operation.
 - vulnerabilities: it will not works when the difference among nearby values after sorting are still significantly large. Also, there are many large negative values, it might reach -FLT_MAX, thus casues overflow.

 2c) averageC:
 - method: sort the array in descsending order of absolute values, and then sum them up one by one, finally divided by the array size.
 - strengths: after sorting, it adds the values by descsending order, if the nearby values have opposite sign, the sum will reduce the magnitude, and thus make less addition rounding error for following values.
 - vulnerabilities: if the nearby values have the same sign, it will cause a even larger magnitude number, which might results in either overflow or significant addtion rounding error for the following values. 

3) bbsort

3a) function name: compare_keys, it has 44 instructions
3b) print the two elements being compared: p (char*)$rbp => 0x605480 "16006", p (char*)$r12 => 0x6054a0 "10"
3c)
    global variable is # 0x603180 <option_mask32>
    by:     p $ebx, p/t $ebx, p/x $ebx
    -n -r:    257 / 100000001 / 0x101
    -r:       256 / 100000000 / 0x100
    -n -r -u: 265 / 100001001 / 0x109

    Conclusion: the global value is an interger, the default without flag has value 0.
      -r flag add 1 bit at 9th digit from right, -n add 1 bit at 1th digit, -u add 1 bit at 4th digit.

3d) to print array in qsort function: p *(char**)b@24 ,
    to print array outside qsort: p *(char**)0x605270@24
    - for -r, the array is actually sorted in reverse order
    - for -u, dupliactes are removed after sorting.
    - for -n, each line is repeatedly converted to a number to compare.


