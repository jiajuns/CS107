# Lab1 Learning notes

## Roundup

The answer for this section is in `round.c`
### is_power_of_2
```c
bool is_power_of_2(unsigned int x){
    return (x & (x - 1)) == 0;
}
```
If a integer is a power of 2, it bits representation has the form like this `10000`, and its value minus 1 has the form like `01111`. Then after doing the and operation the result will be `00000`.

### round_up
This program is to round up the first number to be nearest multiple of the second number.

When the second value is not the power of 2:
```c
    return ((val + mult -1) / mult) * mult;
```

When the second value is the power of 2:
```c
    return ((val + mult -1) & ~(mult -1));
```
`mult -1` has form of `0011111`, then `~(mult -1)` has form of `1100000`. This means all the bits where `mult` has value will be converted to 0 and the first element of `mult` will be keeped as 1.

Then when val is smaller than `mult`, it will only modify the elements where are zeros. After doing and operation, the result will be `0100000`, which is `mult`； when `val` is eqaul or larger than `mult`, `val + mult -1` has the form like `1*******`, all the bits marked as `*` are not relevent after AND operation. The result will be the next value that is twice as big as `mult` or equal to its value.

## Midpoint
Here I only show the final version of midpoint algorithm, since other methods are easy to understand.
```c
int mid_C(int x. int y){
    return (x & y) + ((x ^ y) >> 1);
}
```
`x & y` pulls udentify which power of 2 contained in both x and y. Those power of 2 bits will remain the same in the midpoint integer. `(x ^ y) >> 1` will pulls out the different power of 2 for x and y. After being dvided, those different power of 2 will shift to the left by 1. Then after added these two parts together, the result is the midpoint value.

## Parity
The result is in the code.