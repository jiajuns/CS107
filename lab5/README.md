# lab5

## observe float
1. When float overflows, it becomes `inf` or `-inf`
2. Floats divide by zero becomes `inf`, it dose not halt the program
3. 
    There are two types of exceptional value of float: `inf` and `nan`, when float overflows result in `inf` or float divide by zero. It is still valid to do comparision for `inf` and all the math holds true for `inf`. However `inf - inf` result in `-nan`.

    And when `0.0/0.0` result in `nan`. Mathmatic and computation for `nan` will result in `nan`; and all the comparision for `nan` results in `false`

## fmax
1. The manual says if one argument is `NaN`, the other argument is returned; if two arguments are `NaN`, then `NaN` is returned. `inf` is not dealt differently since, all the math comparsion still hold for `inf`.
2. If line 1-4 are removed, whenever there is `NaN`, the program will always return the first argument.
3. The comparison `-0.0 < 0.0` is false, but `signbit(-0.0)` will return a nonzero value. Also `NaN` has signed bits.

## Nearest representation

## hypotenuse
1. The navie version has overflow when `x or y > 1e64` and has under flow when `x or y < 1e-64`. When overflow or underflow happens the result will be `inf` or `-inf`
2. The expected range for `r` is `[0, 1]`, and it will not overflow or underflow. Since `min < max` it will not overflow and when `min << max`, `r=0`
3. Yes it can hanle value that is problematic for naive version
4. It can still overflow but it will overflow only when `x` or `y` close to `FLT_max` or `FLT_MIN`.