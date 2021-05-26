#include <Arduino.h>
#include "fast_div.h"

template <typename F>
unsigned long elapsed_time(unsigned long iterations, F f)
{
    auto startTime = micros();

    for (unsigned long loop=0; loop<iterations; ++loop)
    {
      f();
    }

    auto stopTime = micros();
    return stopTime-startTime;
}

template <typename testFunc>
void testCheckSum(testFunc func)
{
  unsigned long checkSum = 0;
  unsigned long iterations = INT8_MAX/16;

  unsigned long testTime = elapsed_time(iterations, 
    [&checkSum, &func]() { func(checkSum); }
  );
  Serial.print(checkSum); Serial.print(" "); Serial.print(testTime);      
}

#define TEST_DIV(OPERATION, Div) \
[](unsigned long &checkSum) \
{ \
  for (int16_t loop = -8192; loop < 8192; ++loop) \
  { \
    checkSum += OPERATION(loop, Div); \
  } \
}
#define NATIVE_DIV(Operand, Div) (Operand / Div)
#define TEST_NATIVE_DIV(Div) TEST_DIV(NATIVE_DIV, Div)
#define SHIFT_MUL_DIV(Operand, Div) FAST_DIV16(Operand, Div)
#define TEST_FAST_DIV(Div) TEST_DIV(SHIFT_MUL_DIV, Div)

#define TEST_MOD(OPERATION, Div)\
[](unsigned long &checkSum) \
{ \
  for (uint16_t loop = 0; loop <8192; ++loop) \
  { \
    checkSum += OPERATION(loop, Div); \
  } \
}
#define NATIVE_MOD(Operand, Div) (Operand % Div)
#define TEST_NATIVE_MOD(Div) TEST_MOD(NATIVE_MOD, Div)
#define SHIFT_MUL_MOD(Operand, Div) FAST_MOD16(Operand, Div)
#define TEST_FAST_MOD(Div) TEST_MOD(SHIFT_MUL_MOD, Div)

void setup() {
  Serial.begin(9600);

  #include "test.g.hpp"
}

void loop() {
}