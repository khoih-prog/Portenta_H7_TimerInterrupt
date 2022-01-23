/****************************************************************************************************************************
  Portenta_H7_TimerInterrupt.h
  For Portenta_H7 boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/Portenta_H7_TimerInterrupt
  Licensed under MIT license

  Now even you use all these new 16 ISR-based timers,with their maximum interval practically unlimited (limited only by
  unsigned long miliseconds), you just consume only one Portenta_H7 STM32 timer and avoid conflicting with other cores' tasks.
  The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers
  Therefore, their executions are not blocked by bad-behaving functions / tasks.
  This important feature is absolutely necessary for mission-critical tasks.

  Version: 1.4.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.2.1   K.Hoang      15/09/2021 Initial coding for Portenta_H7
  1.3.0   K.Hoang      17/09/2021 Add PWM features and examples
  1.3.1   K.Hoang      21/09/2021 Fix warnings in PWM examples
  1.4.0   K.Hoang      22/01/2022 Fix `multiple-definitions` linker error. Fix bug
*****************************************************************************************************************************/

#pragma once

#ifndef PORTENTA_H7_TIMERINTERRUPT_H
#define PORTENTA_H7_TIMERINTERRUPT_H

#if ( ( defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) ) && defined(ARDUINO_ARCH_MBED) )
  #warning Use MBED ARDUINO_PORTENTA_H7 and LittleFS
  
  #if defined(BOARD_NAME)
    #undef BOARD_NAME
  #endif

  #if defined(CORE_CM7)
    #warning Using Portenta H7 M7 core
    #define BOARD_NAME              "PORTENTA_H7_M7"
  #else
    #warning Using Portenta H7 M4 core
    #define BOARD_NAME              "PORTENTA_H7_M4"
  #endif
  
#else
  #error This code is intended to run on the MBED ARDUINO_PORTENTA_H7 platform! Please check your Tools->Board setting. 
#endif

#ifndef PORTENTA_H7_TIMER_INTERRUPT_VERSION
  #define PORTENTA_H7_TIMER_INTERRUPT_VERSION       "Portenta_H7_TimerInterrupt v1.4.0"
  
  #define PORTENTA_H7_TIMER_INTERRUPT_VERSION_MAJOR      1
  #define PORTENTA_H7_TIMER_INTERRUPT_VERSION_MINOR      4
  #define PORTENTA_H7_TIMER_INTERRUPT_VERSION_PATCH      0

  #define PORTENTA_H7_TIMER_INTERRUPT_VERSION_INT        1004000  
#endif


///////////////////////////////////////////

#include "stm32/HardwareTimer.h"

///////////////////////////////////////////

#if defined(ARDUINO)
  #if ARDUINO >= 100
    #include <Arduino.h>
  #else
    #include <WProgram.h>
  #endif
#endif

#include "TimerInterrupt_Generic_Debug.h"

class Portenta_H7_TimerInterrupt;

typedef Portenta_H7_TimerInterrupt Portenta_H7_Timer;

typedef void (*timerCallback)  ();


class Portenta_H7_TimerInterrupt
{
  private:
    TIM_TypeDef*    _timer;
    HardwareTimer*  _hwTimer = NULL;

    timerCallback   _callback;        // pointer to the callback function
    float           _frequency;       // Timer frequency
    uint32_t        _timerCount;      // count to activate timer

  public:

    Portenta_H7_TimerInterrupt(TIM_TypeDef* timer)
    {
      _timer = timer;
      
      _hwTimer = new HardwareTimer(_timer);
      
      _callback = NULL;
    };
    
    ~Portenta_H7_TimerInterrupt()
    {
      if (_hwTimer)
        delete _hwTimer;
    }
    
    #define TIM_CLOCK_FREQ      ( (float) 1000000.0f )

    // frequency (in hertz) and duration (in milliseconds). Duration = 0 or not specified => run indefinitely
    // No params and duration now. To be addes in the future by adding similar functions here or to STM32-hal-timer.c
    bool setFrequency(float frequency, timerCallback callback)
    {
      if ( (frequency == 0.0f) || (frequency > 100000.0f) || (callback == NULL) )
      {
        TISR_LOGERROR(F("Error. frequency == 0, higher than 100KHz or callback == NULL "));
      
        return false;
      }
        
      // select timer frequency is 1MHz for better accuracy. We don't use 16-bit prescaler for now.
      // Will use later if very low frequency is needed.
      //_frequency  = 1000000;
      //_timerCount = (uint32_t) _frequency / frequency;
      
      //TISR_LOGWARN1(F("Portenta_H7_TimerInterrupt: Timer Input Freq (Hz) ="), _hwTimer->getTimerClkFreq());
      //TISR_LOGWARN3(F("Frequency ="), _frequency, F(", _count ="), (uint32_t) (_timerCount));
      
      // Hardware timer is preset in RP2040 at 1MHz / 1uS
      _frequency  = frequency;
      _timerCount = (uint32_t) TIM_CLOCK_FREQ / frequency;
      
      TISR_LOGWARN1(F("Timer Input Freq (Hz) = "), _hwTimer->getTimerClkFreq());
      TISR_LOGWARN3(F("Frequency ="), _frequency, F(", _count = "), (uint32_t) (_timerCount));
      
      _hwTimer->setCount(0, MICROSEC_FORMAT);
      
      _hwTimer->setOverflow(_timerCount, MICROSEC_FORMAT);
      //////

      _hwTimer->attachInterrupt(callback);
      _hwTimer->resume();

      return true;
    }

    // interval (in microseconds) and duration (in milliseconds). Duration = 0 or not specified => run indefinitely
    // No params and duration now. To be addes in the future by adding similar functions here or to STM32-hal-timer.c
    bool setInterval(unsigned long interval, timerCallback callback)
    {
      return setFrequency((float) (1000000.0f / interval), callback);
    }

    bool attachInterrupt(float frequency, timerCallback callback)
    {
      return setFrequency(frequency, callback);
    }

    // interval (in microseconds) and duration (in milliseconds). Duration = 0 or not specified => run indefinitely
    // No params and duration now. To be addes in the future by adding similar functions here or to STM32-hal-timer.c
    bool attachInterruptInterval(unsigned long interval, timerCallback callback)
    {
      return setFrequency( (float) ( 1000000.0f / interval), callback);
    }

    void detachInterrupt()
    {
      _hwTimer->detachInterrupt();
    }

    void disableTimer()
    {
      //_hwTimer->detachInterrupt();
      _hwTimer->pause();
    }

    // Duration (in milliseconds). Duration = 0 or not specified => run indefinitely
    void reattachInterrupt()
    {
      setFrequency(_frequency, _callback);
    }

    // Duration (in milliseconds). Duration = 0 or not specified => run indefinitely
    void enableTimer()
    {
      //setFrequency(_frequency, _callback);
      _hwTimer->setCount(0, MICROSEC_FORMAT);
      _hwTimer->resume();
    }

    // Just stop clock source, clear the count
    void stopTimer()
    {
      _hwTimer->pause();
      _hwTimer->setCount(0, MICROSEC_FORMAT);
    }

    // Just reconnect clock source, start current count from 0
    void restartTimer()
    {
      _hwTimer->setCount(0, MICROSEC_FORMAT);
      _hwTimer->resume();
    }
}; // class Portenta_H7_TimerInterrupt

#endif    // PORTENTA_H7_TIMERINTERRUPT_H

