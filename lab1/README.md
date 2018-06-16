# Lab1 Learning notes

## Roundup

The answer for this section is in `round.c`
### is_power_of_2
```
bool is_power_of_2(unsigned int x){
    return (x & (x - 1)) == 0;
}
```
If a integer is a power of 2, it bits representation has the form like this `10000`, and its value minus 1 has the form like `01111`. Then after doing the and operation the result will be `00000`.

### round_up
This program is to round up the first number to be nearest multiple of the second number.

When the second value is not the power of 2:
```
    return ((val + mult -1) / mult) * mult;
```

When the second value is the power of 2:
```
    return ((val + mult -1) & ~(mult -1));
```
`mult -1` has form of `0011111`, then `~(mult -1)` has form of `1100000`. This means all the bits where `mult` has value will be converted to 0 and the first element of `mult` will be keeped as 1.

Then when val is smaller than `mult`, it will only modify the elements where are zeros. After doing and operation, the result will be `0100000`, which is `mult`； when `val` is eqaul or larger than `mult`, `val + mult -1` has the form like `1*******`, all the bits marked as `*` are not relevent after AND operation. The result will be the next value that is twice as big as `mult` or equal to its value.

## Midpoint
