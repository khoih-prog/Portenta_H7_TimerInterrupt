/****************************************************************************************************************************
  TimerInterruptTest.ino
  For Portenta_H7 boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/Portenta_H7_TimerInterrupt
  Licensed under MIT license

  Now even you use all these new 16 ISR-based timers,with their maximum interval practically unlimited (limited only by
  unsigned long miliseconds), you just consume only one Portenta_H7 STM32 timer and avoid conflicting with other cores' tasks.
  The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers
  Therefore, their executions are not blocked by bad-behaving functions / tasks.
  This important feature is absolutely necessary for mission-critical tasks.
*****************************************************************************************************************************/
/*
   Notes:
   Special design is necessary to share data between interrupt code and the rest of your program.
   Variables usually need to be "volatile" types. Volatile tells the compiler to avoid optimizations that assume
   variable can not spontaneously change. Because your function may change variables while your program is using them,
   the compiler needs this hint. But volatile alone is often not enough.
   When accessing shared variables, usually interrupts must be disabled. Even with volatile,
   if the interrupt changes a multi-byte variable between a sequence of instructions, it can be read incorrectly.
   If your data is multiple variables, such as an array and a count, usually interrupts need to be disabled
   or the entire sequence of your code which accesses the data.
*/

#if !( ( defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) ) && defined(ARDUINO_ARCH_MBED) )
  #error This code is designed to run on Portenta_H7 platform! Please check your Tools->Board setting.
#endif

// These define's must be placed at the beginning before #include "Portenta_H7_TimerInterrupt.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define _TIMERINTERRUPT_LOGLEVEL_     4

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "Portenta_H7_TimerInterrupt.h"

#define LED_OFF             HIGH
#define LED_ON              LOW

#ifndef LED_BUILTIN
  #define LED_BUILTIN       24    //LEDG               // Pin 24 control on-board LED_GREEN on Portenta_H7
#endif

#ifndef LED_BLUE
  #define LED_BLUE          25    //LEDB               // Pin 25 control on-board LED_BLUE on Portenta_H7
#endif

#ifndef LED_RED
  #define LED_RED           23   // LEDR              // Pin 23 control on-board LED_RED on Portenta_H7
#endif

unsigned int SWPin = D5;

// In Portenta_H7, avoid doing something fancy in ISR, for example Serial.print
// Or you can get this run-time error / crash

void TimerHandler0()
{
  static bool toggle0 = false;

  //timer interrupt toggles pin LED_BUILTIN
  digitalWrite(LED_BUILTIN, toggle0);
  toggle0 = !toggle0;
}

void TimerHandler1()
{
  static bool toggle1 = false;

  //timer interrupt toggles outputPin
  digitalWrite(LED_BLUE, toggle1);
  digitalWrite(SWPin, toggle1);
  toggle1 = !toggle1;
}

#define TIMER0_INTERVAL_MS        1000
#define TIMER0_DURATION_MS        10000

#define TIMER1_INTERVAL_MS        3000
#define TIMER1_DURATION_MS        30000

// Depending on the board, you can select STM32H7 Hardware Timer from TIM1-TIM22
// If you select a Timer not correctly, you'll get a message from compiler
// 'TIMxx' was not declared in this scope; did you mean 'TIMyy'? 

// Portenta_H7 OK       : TIM1, TIM4, TIM7, TIM8, TIM12, TIM13, TIM14, TIM15, TIM16, TIM17
// Portenta_H7 Not OK   : TIM2, TIM3, TIM5, TIM6, TIM18, TIM19, TIM20, TIM21, TIM22
// Portenta_H7 No timer : TIM9, TIM10, TIM11. Only for STM32F2, STM32F4 and STM32L1 
// Portenta_H7 No timer : TIM18, TIM19, TIM20, TIM21, TIM22

// Init timer TIM15
Portenta_H7_Timer ITimer0(TIM15);
// Init  timer TIM16
Portenta_H7_Timer ITimer1(TIM16);

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  pinMode(LED_BUILTIN,  OUTPUT);
  pinMode(LED_BLUE,     OUTPUT);
  pinMode(SWPin,        OUTPUT); 

  digitalWrite(LED_BUILTIN, LED_OFF);
  digitalWrite(LED_BLUE,    LED_OFF);
  digitalWrite(SWPin,       LOW);
  
  delay(100);

  Serial.print(F("\nStarting TimerInterruptTest on ")); Serial.println(BOARD_NAME);
  Serial.println(PORTENTA_H7_TIMER_INTERRUPT_VERSION);

  // Interval in microsecs
  if (ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0))
  {
    Serial.print(F("Starting ITimer0 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer0. Select another freq. or timer"));

  // Interval in microsecs
  if (ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS * 1000, TimerHandler1))
  {
    Serial.print(F("Starting  ITimer1 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer1. Select another freq. or timer")); 
}

void loop()
{
  static unsigned long lastTimer0 = 0;
  static unsigned long lastTimer1 = 0;

  static bool timer0Stopped         = false;
  static bool timer1Stopped         = false;

  if (millis() - lastTimer0 > TIMER0_DURATION_MS)
  {
    lastTimer0 = millis();

    if (timer0Stopped)
    {
      Serial.print(F("Start ITimer0, millis() = ")); Serial.println(millis());
      ITimer0.restartTimer();
    }
    else
    {
      Serial.print(F("Stop ITimer0, millis() = ")); Serial.println(millis());
      ITimer0.stopTimer();
    }
    timer0Stopped = !timer0Stopped;
  }

  if (millis() - lastTimer1 > TIMER1_DURATION_MS)
  {
    lastTimer1 = millis();

    if (timer1Stopped)
    {
      Serial.print(F("Start ITimer1, millis() = ")); Serial.println(millis());
      ITimer1.restartTimer();
    }
    else
    {
      Serial.print(F("Stop ITimer1, millis() = ")); Serial.println(millis());
      ITimer1.stopTimer();
    }
    
    timer1Stopped = !timer1Stopped;
  }
}
