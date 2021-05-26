#pragma once
#include <Arduino.h>
#include "integer_division_uint16.h"

#define CAT_HELPER(a, b) a ## b
#define CONCAT(A, B) CAT_HELPER(A, B)

/*
* When dividing by a known compile time constant, the division can be replaced
* by a multiply+shift operation. 
*
* Testing on an AtMega2560 shows between 13% & 80%+ speed up for division by
* non-powers of 2. Accuracy confirmed with numerator [-8192, 8192] and
* denominator [0, 1024] (no time to go further, but I'm confident it will work)
*  
* Note: testing of the multiply+shift technique on 8-bit division showed a 
* slight slow down over native code on AtMega2560. So the 8 bit equivalent 
* macros have not been included
*/

/*
* Wrapper for *unsigned* 16-bit DIVISION. The divisor must be a compile time
* constant.
* E.g. FAST_DIV16U(value, 100)
*/
#define FAST_DIV16U(a, d) CONCAT(U16DIVBY, d)(a)

/*
* Wrapper for *signed* 16-bit DIVISION. The divisor must be a compile time
* constant. Will be slightly slower than FAST_DIV16U
* E.g. FAST_DIV16(value, -100)
*/
#define FAST_DIV16(a, d) (a>=0 ? (int16_t)FAST_DIV16U(a, d) : (int16_t)-(FAST_DIV16U(-a, d)))

/*
* Wrapper for *unsigned* 16-bit MODULUS. The divisor must be a compile time
* constant. 
* E.g. FAST_MOD16U(value, 6)
*/
#define FAST_MOD16U(a, d) (a - (FAST_DIV16U(a, d) * d))