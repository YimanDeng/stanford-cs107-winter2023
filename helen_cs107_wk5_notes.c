#include<stdio.h>
#include<stdlib.h>
/*
1. Floating point numbers
  How to represent real numbers in a computer?
  Constraints: 
    Want fixed number of bits. So we can't represent a number exactly.
    Want to represent a large range of numbers
    Want to be able to do operations on the numbers
  Fixed point:
    e.g., 10^2, 10^1, 10^0, 10^-1, 10^-2. Arithmetic is pretty simple. But range is 0 to 999.99. The range is set by where we fix the decimal place.
  Floating point:
    V = x * 2^y. exponent and fractional value
    Fractional values in binary, similar https://web.stanford.edu/class/cs107/float/
    Interesting, .1 in binary fraction is like 1/3 in decimal fraction, .1 repeats like 0.000110011...
    Left and right shift of binary point - the number is divided or multiplied by 2
    0.1111111... is the number just below 1, i.e., 1 - epsilon
  IEEE floating point: 
    V = (-1)^s * 2^E * M
    sign bit s is 1 or 0
    scaling factor E weights value by power of 2. 
    Mantissa M is the digits of the number, is a fractional binary value that ranges either between [1, 2 - epsilon] or [0, 1 - epsilon]
    For single, 1 + 8 + 23 = 32 bits
    For double, 1 + 11 + 52 = 64 bits
  You don't want to use floating point for something like banking
  
  A float is normalized if the exponent is not all 1s and not all 1s
  exponent value is signed exponent in biased form: value - (2^k - 1) = actual exponent, e.g., 126-127 = -1.
  fraction f represents 0.f1f2f3... with implied leading 1
  
  When is floating point number an integer? the fractional part of the significand is equal to 0
  When exponents is all zeros, denormalized, the bias is now 1 less, the significand value now without the leading 1.
  0 represented with all 0s.
  When exponents all ones, exceptional form 0 1...1 0...0 is +infinity, sign bit 1 is -infinity
  Eceptional numbers also define NaN, not a number.
  
  Arithmetic with floating point numbers
    not enough precision if you try to do between 2 numbers of very different orders
    0.1 + 0.2 != 0.3
    float equality, sometimes you can't differentiate 2 different numbers due to pimited precision
*/
float f = 0.1; 
// print with 27 decimal places
printf("%.27f\n",f);
