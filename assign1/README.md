# Assignment 1

## Saturating Arithmetic
This program has three main functions. 1) Return the minimum value of a signed int with specified bitwidth. 2) Return the maximum value of a signed int with specified bitwidth. 3) A summation function that add up two value.

```c
long signed_min(int bitwidth){
    return ~0L << (bitwidth-1);
}
```
This program requires familarity with the signed number circle, the minimal value of a bitwidth has the form like `10000000`, then if stores it in `long`, it has form like `*~10000000`. This can be obtained by shifting `~*1` to the left by `bitwidth-1`


```c
long signed_max(int bitwidth){
    return (1L << (bitwidth-1))-1; 
}
```
The maximum value has form such as `01111111`. This can be achieved by `1000000 - 1`.


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
The logic of this function is to return sum value directly if it dose not overflow or underflow. If overflow or underflow then return the max and min value respectively. In order to tell whether the value overflow or not, here I do a `&` operation between `sum` and `2^(bitwidth+1)-1`. This will tell me whether the value has overflow to the next bit position. The same logic can be applied for underflow.

## Cellular automata
This question requires a lot of reading, lets skip it for now

## UTF-8
```c
int to_utf8(unsigned short cp, unsigned char seq[]){
    //if sigbits are less than 7
    if (cp >> 7 == 0){
        seq[0] = cp;
        return 1
    } else if (cp >> 11 == 0){
        seq[0] = (1 << 7) + (1 << 6) + (cp >> 6);
        seq[1] = (1 << 7) + (cp & 0x3f);
        return 2;
    } else {
        seq[0] = (1 << 7) + (1 << 6) + (1 << 5) + (cp << 12);
        seq[1] = (1 << 7) + ((cp >> 6) & 0x3f);
        seq[2] = (1 << 7) + ((cp >> 6) & 0x3f);
        return 3;
    }
}
```
The trick of this program is to know the data type of the input. The input after the utility function has been converted to int type that can be applied with bitwise operation. 

In order to convert to UTF-8 encoded bytes, the pattern of UTF-8 encoded bytes pattern:
1. num sigbits smaller than 7, `0xxxxxxx`
2. num sigbits between 8 and 11, `110xxxxx` and `10xxxxx`
3. num sigbits larger than 11, `1110xxxx`, `10xxxxxx`, `10xxxxxx`.

The logic of the function is to figure out which pattern it should follow and fill the bytes pattern. A little trick is to use hex value to represents binary bits, where `0x3f = 111111`.