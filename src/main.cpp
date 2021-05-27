#include <Arduino.h>
#include "fast_div.h"

typedef unsigned long (*pCheckSumFunc)(unsigned long);
void testCheckSum(pCheckSumFunc func)
{
  unsigned long iterations = INT8_MAX/16;

  auto startTime = micros();

  unsigned long checkSum = 0;
  for (unsigned long loop=0; loop<iterations; ++loop)
  {
    checkSum += func(checkSum);
  }

  auto stopTime = micros();
  auto elapsed = stopTime-startTime;

  Serial.print(checkSum); Serial.print(" "); Serial.print(elapsed);      
}

#define TEST_FUNC_NAME(Op, Div) testDiv ## Op ## Div

#define TEST_DIV(OPERATION, Op, Div) \
unsigned long TEST_FUNC_NAME(Op, Div)(unsigned long checkSum) \
{ \
  for (int16_t loop = -8192; loop < 8192; ++loop) \
  { \
    checkSum += OPERATION(loop, Div); \
  } \
  return checkSum; \
}

#define NATIVE_DIV(Operand, Div) (Operand / Div)
#define TEST_NATIVE_DIV(Div) TEST_DIV(NATIVE_DIV, Native, Div)
#define SHIFT_MUL_DIV(Operand, Div) FAST_DIV16(Operand, Div)
#define TEST_FAST_DIV(Div) TEST_DIV(SHIFT_MUL_DIV, ShiftMul, Div)

#include "test_declares.g.hpp"

void setup() {
  Serial.begin(9600);

  #include "test.g.hpp"
}

void loop() {
}