# Assignment 1

## Saturating Arithmetic
This program has three main functions. 1) Return the minimum value of a signed int with specified bitwidth. 2) Return the maximum value of a signed int with specified bitwidth. 3) A summation function that add up two value.

```c
long signed_min(int bitwidth){
    return ~0L << (bitwidth-1);
}
```

```c
long signed_max(int bitwidth){
    return (1L << (bitwidth-1))-1; 
}
```

```c
long sat_add(long operand1, long operand2, int bitwidth){
    long sum = operand1 + operand2;
    if (((1L << 63) & sum == 0) & ((1L << bitwidth-1) & sum != 0)){
        return signed_max(bitwidth);
    }

    if (((1L << 63) & sum != 0) & ((1L << bitwidth-1) & sum == 0)){
        return signed_min(bitwidth);
    }
    return sum;
}
```