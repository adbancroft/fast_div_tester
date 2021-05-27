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

// GCC produces quick code for powers of 2
#undef U16DIVBY1
#define U16DIVBY1(A)    (A)
#undef U16DIVBY2
#define U16DIVBY2(A)    (A / 2U)
#undef U16DIVBY4
#define U16DIVBY4(A)    (A / 4U)
#undef U16DIVBY8
#define U16DIVBY8(A)    (A / 8U)
#undef U16DIVBY16
#define U16DIVBY16(A)    (A / 16U)
#undef U16DIVBY32
#define U16DIVBY32(A)    (A / 32U)
#undef U16DIVBY64
#define U16DIVBY64(A)    (A / 64U)
#undef U16DIVBY128
#define U16DIVBY128(A)    (A / 128U)
#undef U16DIVBY256
#define U16DIVBY256(A)    (A / 256U)
#undef U16DIVBY512
#define U16DIVBY512(A)    (A / 512U)
#undef U16DIVBY1024
#define U16DIVBY1024(A)    (A / 1024U)
#undef U16DIVBY2048
#define U16DIVBY2048(A)    (A / 2048U)
#undef U16DIVBY4096
#define U16DIVBY4096(A)    (A / 4096U)
#undef U16DIVBY8192
#define U16DIVBY8192(A)    (A / 8192U)
#undef U16DIVBY16384
#define U16DIVBY16384(A)    (A / 16384U)
#undef U16DIVBY32768
#define U16DIVBY32768(A)    (A / 32768U)