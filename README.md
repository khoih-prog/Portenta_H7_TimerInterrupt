# Portenta_H7_TimerInterrupt Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/Portenta_H7_TimerInterrupt.svg?)](https://www.ardu-badge.com/Portenta_H7_TimerInterrupt)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Portenta_H7_TimerInterrupt.svg)](https://github.com/khoih-prog/Portenta_H7_TimerInterrupt/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/Portenta_H7_TimerInterrupt/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Portenta_H7_TimerInterrupt.svg)](http://github.com/khoih-prog/Portenta_H7_TimerInterrupt/issues)

---
---

## Table of Contents

* [Why do we need this Portenta_H7_TimerInterrupt library](#why-do-we-need-this-Portenta_H7_TimerInterrupt-library)
  * [Features](#features)
  * [Why using ISR-based Hardware Timer Interrupt is better](#why-using-isr-based-hardware-timer-interrupt-is-better)
  * [Currently supported Boards](#currently-supported-boards)
  * [Important Notes about ISR](#important-notes-about-isr)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Portenta_H7 boards using Arduino IDE in Linux](#1-for-portenta_h7-boards-using-arduino-ide-in-linux)
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)
* [More useful Information about STM32 Timers](#more-useful-information-about-stm32-timers)
* [Available Timers for Portenta_H7](#available-timers-for-portenta_h7)
* [From v1.2.1](#from-v121)
* [Usage](#usage)
  * [1. Using only Hardware Timer directly](#1-using-only-hardware-timer-directly)
    * [1.1 Init Hardware Timer](#11-init-hardware-timer)
    * [1.2 Set Hardware Timer Interval and attach Timer Interrupt Handler function](#12-set-hardware-timer-interval-and-attach-timer-interrupt-handler-function)
  * [2. Using 16 ISR_based Timers from 1 Hardware Timer](#2-using-16-isr_based-timers-from-1-hardware-timer)
    * [2.1 Init Hardware Timer and ISR-based Timer](#21-init-hardware-timer-and-isr-based-timer)
    * [2.2 Set Hardware Timer Interval and attach Timer Interrupt Handler functions](#22-set-hardware-timer-interval-and-attach-timer-interrupt-handler-functions)
* [Examples](#examples)
  * [1. TimerInterrupt](#1-TimerInterrupt)
    * [ 1. Argument_None](examples/Argument_None)
    * [ 2. **Change_Interval**](examples/Change_Interval)
    * [ 3. ISR_16_Timers_Array](examples/ISR_16_Timers_Array)
    * [ 4. **ISR_16_Timers_Array_Complex**](examples/ISR_16_Timers_Array_Complex)
    * [ 5. SwitchDebounce](examples/SwitchDebounce)
    * [ 6. TimerInterruptLEDDemo](examples/TimerInterruptLEDDemo)
    * [ 7. TimerInterruptTest](examples/TimerInterruptTest)
   [2. Multichannel PWM](#2-Multichannel-PWM) 
    * [ 8. PWM_Multi](examples/PWM/PWM_Multi)
    * [ 9. PWM_Multi_Args](examples/PWM/PWM_Multi_Args)
* [Example ISR_16_Timers_Array_Complex](#example-isr_16_timers_array_complex)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. ISR_16_Timers_Array_Complex on PORTENTA_H7_M7](#1-isr_16_timers_array_complex-on-portenta_h7_m7)
  * [2. TimerInterruptTest on PORTENTA_H7_M7](#2-timerinterrupttest-on-portenta_h7_m7)
  * [3. Argument_None on PORTENTA_H7_M7](#3-argument_none-on-portenta_h7_m7)
  * [4. Change_Interval on PORTENTA_H7_M7](#4-change_interval-on-portenta_h7_m7)
  * [5. ISR_16_Timers_Array on PORTENTA_H7_M7](#5-isr_16_timers_array-on-portenta_h7_m7)
  * [6. PWM_Multi_Args on PORTENTA_H7_M7](#6-PWM_Multi_Args-on-portenta_h7_m7)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Why do we need this [Portenta_H7_TimerInterrupt library](https://github.com/khoih-prog/Portenta_H7_TimerInterrupt)

### Features

This library enables you to use Interrupt from Hardware Timers on an **STM32H7-based Portenta_H7** board. 

As **Hardware Timers are rare, and very precious assets** of any board, this library now enables you to use up to **16 ISR-based Timers, while consuming only 1 Hardware Timer**. Timers' interval is very long (**ulong millisecs**).

Now with these new **16 ISR-based timers**, the maximum interval is **practically unlimited** (limited only by unsigned long miliseconds) while **the accuracy is nearly perfect** compared to software timers. 

The most important feature is they're ISR-based timers. Therefore, their executions are **not blocked by bad-behaving functions / tasks**. This important feature is absolutely necessary for mission-critical tasks. 

The [**ISR_16_Timers_Array_Complex**](examples/ISR_16_Timers_Array_Complex) example will demonstrate the nearly perfect accuracy compared to software timers by printing the actual elapsed millisecs of each type of timers.

The [**PWM_Multi_Args**](examples/PWM/PWM_Multi_Args) will demonstrate the usage of multichannel PWM using multiple Hardware Timers. The 6 independent Hardware Timers are used **to control 6 different PWM outputs**, with totally independent frequencies and dutycycles.

Being ISR-based timers, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet or Blynk services. You can also have many `(up to 16)` timers to use.

This non-being-blocked important feature is absolutely necessary for mission-critical tasks.

You'll see blynkTimer Software is blocked while system is connecting to WiFi / Internet / Blynk, as well as by blocking task 
in loop(), using delay() function as an example. The elapsed time then is very unaccurate

#### Why using ISR-based Hardware Timer Interrupt is better

Imagine you have a system with a **mission-critical** function, measuring water level and control the sump pump or doing something much more important. You normally use a software timer to poll, or even place the function in loop(). But what if another function is **blocking** the loop() or setup().

So your function **might not be executed, and the result would be disastrous.**

You'd prefer to have your function called, no matter what happening with other functions (busy loop, bug, etc.).

The correct choice is to use a Hardware Timer with **Interrupt** to call your function.

These hardware timers, using interrupt, still work even if other functions are blocking. Moreover, they are much more **precise** (certainly depending on clock frequency accuracy) than other software timers using millis() or micros(). That's necessary if you need to measure some data requiring better accuracy.

Functions using normal software timers, relying on loop() and calling millis(), won't work if the loop() or setup() is blocked by certain operation. For example, certain function is blocking while it's connecting to WiFi or some services.

The catch is **your function is now part of an ISR (Interrupt Service Routine), and must be lean / mean, and follow certain rules.** More to read on:

[**HOWTO Attach Interrupt**](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)

---

### Currently supported Boards

1. **Portenta_H7 boards** such as Portenta_H7 Rev2 ABX00042, etc., using [**ArduinoCore-mbed mbed_portenta** core](https://github.com/arduino/ArduinoCore-mbed)

---

#### Important Notes about ISR

1. Inside the attached function, **delay() won’t work and the value returned by millis() will not increment.** Serial data received while in the function may be lost. You should declare as **volatile any variables that you modify within the attached function.**

2. Typically global variables are used to pass data between an ISR and the main program. To make sure variables shared between an ISR and the main program are updated correctly, declare them as volatile.

---
---

## Prerequisites

 1. [`Arduino IDE 1.8.16+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`ArduinoCore-mbed mbed_portenta core 2.4.1+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino **Portenta_H7** boards, such as **Portenta_H7 Rev2 ABX00042, etc.**. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)

 3. To use with certain example
   - [`SimpleTimer library`](https://github.com/jfturcot/SimpleTimer) for [ISR_16_Timers_Array example](examples/ISR_16_Timers_Array).
---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**Portenta_H7_TimerInterrupt**](https://github.com/khoih-prog/Portenta_H7_TimerInterrupt), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/Portenta_H7_TimerInterrupt.svg?)](https://www.ardu-badge.com/Portenta_H7_TimerInterrupt) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**Portenta_H7_TimerInterrupt**](https://github.com/khoih-prog/Portenta_H7_TimerInterrupt) page.
2. Download the latest release `Portenta_H7_TimerInterrupt-master.zip`.
3. Extract the zip file to `Portenta_H7_TimerInterrupt-master` directory 
4. Copy whole `Portenta_H7_TimerInterrupt-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**Portenta_H7_TimerInterrupt** library](https://platformio.org/lib/show/12828/Portenta_H7_TimerInterrupt) by using [Library Manager](https://platformio.org/lib/show/12828/Portenta_H7_TimerInterrupt/installation). Search for **Portenta_H7_TimerInterrupt** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For Portenta_H7 boards using Arduino IDE in Linux

  **To be able to upload firmware to Portenta_H7 using Arduino IDE in Linux (Ubuntu, etc.)**, you have to copy the file [portenta_post_install.sh](Packages_Patches/arduino/hardware/mbed_portenta/2.4.1/portenta_post_install.sh) into mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/2.4.1/portenta_post_install.sh). 
  
  Then run the following command using `sudo`
  
```
$ cd ~/.arduino15/packages/arduino/hardware/mbed_portenta/2.4.1
$ chmod 755 portenta_post_install.sh
$ sudo ./portenta_post_install.sh
```

This will create the file `/etc/udev/rules.d/49-portenta_h7.rules` as follows:

```
# Portenta H7 bootloader mode UDEV rules

SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="035b", GROUP="plugdev", MODE="0666"
```

Supposing the ArduinoCore-mbed core version is 2.4.1. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/2.4.1/portenta_post_install.sh`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/x.yy.zz/portenta_post_install.sh`

---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using **xyz-Impl.h instead of standard xyz.cpp**, possibly creates certain `Multiple Definitions` Linker error in certain use cases. Although it's simple to just modify several lines of code, either in the library or in the application, the library is adding 2 more source directories

1. **scr_h** for new h-only files
2. **src_cpp** for standard h/cpp files

besides the standard **src** directory.

To use the **old standard cpp** way, locate this library' directory, then just 

1. **Delete the all the files in src directory.**
2. **Copy all the files in src_cpp directory into src.**
3. Close then reopen the application code in Arduino IDE, etc. to recompile from scratch.

To re-use the **new h-only** way, just 

1. **Delete the all the files in src directory.**
2. **Copy the files in src_h directory into src.**
3. Close then reopen the application code in Arduino IDE, etc. to recompile from scratch.

---
---


## More useful Information about STM32 Timers

The Timers of STM32s are numerous, yet very sophisticated and powerful.

In general, across the STM32 microcontrollers families, the timer peripherals that have the same name also have the same features set, but there are a few exceptions. 

The general purpose timers embedded by the STM32 microcontrollers share the same backbone structure; they differ only on the level of features embedded by a given timer peripheral. 

The level of features integration for a given timer peripheral is decided based on the applications field that it targets.

The timer peripherals can be classified as:

• Advanced-configuration timers like TIM1 and TIM8 among others.
• General-purpose configuration timers like TIM2 and TIM3 among others
• Lite-configuration timers like TIM9, TIM10, TIM12 and TIM16 among others
• Basic-configuration timers like TIM6 and TIM7 among others.


More information can be found at [**Embedded-Lab STM32 TIMERS**](http://embedded-lab.com/blog/stm32-timers/)

To be sure which Timer is available for the board you're using, check the Core Package's related files. For example, for **Portenta_H7 using STM32H747XI**, check this file:

1. `~/.arduino15/packages/STM32/hardware/stm32/2.0.0/system/Drivers/CMSIS/Device/ST/STM32H7xx/Include/stm32h7xx.h`


The information will be as follows:

```
typedef struct
{
  __IO uint32_t CR1;         /*!< TIM control register 1,                   Address offset: 0x00 */
  __IO uint32_t CR2;         /*!< TIM control register 2,                   Address offset: 0x04 */
  __IO uint32_t SMCR;        /*!< TIM slave mode control register,          Address offset: 0x08 */
  __IO uint32_t DIER;        /*!< TIM DMA/interrupt enable register,        Address offset: 0x0C */
  __IO uint32_t SR;          /*!< TIM status register,                      Address offset: 0x10 */
  __IO uint32_t EGR;         /*!< TIM event generation register,            Address offset: 0x14 */
  __IO uint32_t CCMR1;       /*!< TIM capture/compare mode register 1,      Address offset: 0x18 */
  __IO uint32_t CCMR2;       /*!< TIM capture/compare mode register 2,      Address offset: 0x1C */
  __IO uint32_t CCER;        /*!< TIM capture/compare enable register,      Address offset: 0x20 */
  __IO uint32_t CNT;         /*!< TIM counter register,                     Address offset: 0x24 */
  __IO uint32_t PSC;         /*!< TIM prescaler,                            Address offset: 0x28 */
  __IO uint32_t ARR;         /*!< TIM auto-reload register,                 Address offset: 0x2C */
  __IO uint32_t RCR;         /*!< TIM repetition counter register,          Address offset: 0x30 */
  __IO uint32_t CCR1;        /*!< TIM capture/compare register 1,           Address offset: 0x34 */
  __IO uint32_t CCR2;        /*!< TIM capture/compare register 2,           Address offset: 0x38 */
  __IO uint32_t CCR3;        /*!< TIM capture/compare register 3,           Address offset: 0x3C */
  __IO uint32_t CCR4;        /*!< TIM capture/compare register 4,           Address offset: 0x40 */
  __IO uint32_t BDTR;        /*!< TIM break and dead-time register,         Address offset: 0x44 */
  __IO uint32_t DCR;         /*!< TIM DMA control register,                 Address offset: 0x48 */
  __IO uint32_t DMAR;        /*!< TIM DMA address for full transfer,        Address offset: 0x4C */
  uint32_t      RESERVED1;   /*!< Reserved, 0x50                                                 */
  __IO uint32_t CCMR3;       /*!< TIM capture/compare mode register 3,      Address offset: 0x54 */
  __IO uint32_t CCR5;        /*!< TIM capture/compare register5,            Address offset: 0x58 */
  __IO uint32_t CCR6;        /*!< TIM capture/compare register6,            Address offset: 0x5C */
  __IO uint32_t AF1;         /*!< TIM alternate function option register 1, Address offset: 0x60 */
  __IO uint32_t AF2;         /*!< TIM alternate function option register 2, Address offset: 0x64 */
  __IO uint32_t TISEL;       /*!< TIM Input Selection register,             Address offset: 0x68 */
} TIM_TypeDef;
```

and

```
#define PERIPH_BASE            0x40000000UL /*!< Base address of : AHB/ABP Peripherals   
/*!< Peripheral memory map */
#define APB1PERIPH_BASE        PERIPH_BASE

/*!< APB1 peripherals */
/*!< D2_APB1PERIPH peripherals */
#define TIM2_BASE             (D2_APB1PERIPH_BASE + 0x0000UL)
#define TIM3_BASE             (D2_APB1PERIPH_BASE + 0x0400UL)
#define TIM4_BASE             (D2_APB1PERIPH_BASE + 0x0800UL)
#define TIM5_BASE             (D2_APB1PERIPH_BASE + 0x0C00UL)
#define TIM6_BASE             (D2_APB1PERIPH_BASE + 0x1000UL)
#define TIM7_BASE             (D2_APB1PERIPH_BASE + 0x1400UL)
#define TIM12_BASE            (D2_APB1PERIPH_BASE + 0x1800UL)
#define TIM13_BASE            (D2_APB1PERIPH_BASE + 0x1C00UL)
#define TIM14_BASE            (D2_APB1PERIPH_BASE + 0x2000UL)

/*!< APB2 peripherals */
#define TIM1_BASE             (D2_APB2PERIPH_BASE + 0x0000UL)
#define TIM8_BASE             (D2_APB2PERIPH_BASE + 0x0400UL)
...
#define TIM9_BASE             (APB2PERIPH_BASE + 0x4000UL)
#define TIM10_BASE            (APB2PERIPH_BASE + 0x4400UL)
#define TIM11_BASE            (APB2PERIPH_BASE + 0x4800UL)
...
#define TI15_BASE            (D2_APB2PERIPH_BASE + 0x4000UL)
#define TIM16_BASE            (D2_APB2PERIPH_BASE + 0x4400UL)
#define TIM17_BASE            (D2_APB2PERIPH_BASE + 0x4800UL)
...
#define HRTIM1_BASE           (D2_APB2PERIPH_BASE + 0x7400UL)
#define HRTIM1_TIMA_BASE      (HRTIM1_BASE + 0x00000080UL)
#define HRTIM1_TIMB_BASE      (HRTIM1_BASE + 0x00000100UL)
#define HRTIM1_TIMC_BASE      (HRTIM1_BASE + 0x00000180UL)
#define HRTIM1_TIMD_BASE      (HRTIM1_BASE + 0x00000200UL)
#define HRTIM1_TIME_BASE      (HRTIM1_BASE + 0x00000280UL)
#define HRTIM1_COMMON_BASE    (HRTIM1_BASE + 0x00000380UL)
...
#define TIM2                ((TIM_TypeDef *) TIM2_BASE)
#define TIM3                ((TIM_TypeDef *) TIM3_BASE)
#define TIM4                ((TIM_TypeDef *) TIM4_BASE)
#define TIM5                ((TIM_TypeDef *) TIM5_BASE)
#define TIM6                ((TIM_TypeDef *) TIM6_BASE)
#define TIM7                ((TIM_TypeDef *) TIM7_BASE)
#define TIM13               ((TIM_TypeDef *) TIM13_BASE)
#define TIM14               ((TIM_TypeDef *) TIM14_BASE)
...
#define TIM1                ((TIM_TypeDef *) TIM1_BASE)
#define TIM8                ((TIM_TypeDef *) TIM8_BASE)
...
#define TIM12               ((TIM_TypeDef *) TIM12_BASE)
#define TIM15               ((TIM_TypeDef *) TIM15_BASE)
#define TIM16               ((TIM_TypeDef *) TIM16_BASE)
#define TIM17               ((TIM_TypeDef *) TIM17_BASE)
...
#define HRTIM1              ((HRTIM_TypeDef *) HRTIM1_BASE)
#define HRTIM1_TIMA         ((HRTIM_Timerx_TypeDef *) HRTIM1_TIMA_BASE)
#define HRTIM1_TIMB         ((HRTIM_Timerx_TypeDef *) HRTIM1_TIMB_BASE)
#define HRTIM1_TIMC         ((HRTIM_Timerx_TypeDef *) HRTIM1_TIMC_BASE)
#define HRTIM1_TIMD         ((HRTIM_Timerx_TypeDef *) HRTIM1_TIMD_BASE)
#define HRTIM1_TIME         ((HRTIM_Timerx_TypeDef *) HRTIM1_TIME_BASE)
#define HRTIM1_COMMON       ((HRTIM_Common_TypeDef *) HRTIM1_COMMON_BASE)
```

---

## Available Timers for Portenta_H7

This is the temporary list for Portenta_H7 Timers which can be used. The available Timers certainly depends on they are being used for other purpose (core, application, libraries, etc.) or not. You have to exhausively test yourself to be sure.

#### 1. OK to use

**TIM1, TIM4, TIM7, TIM8, TIM12, TIM13, TIM14, TIM15, TIM16, TIM17**

#### 2. Not exist

**TIM9, TIM10, TIM11. Only for STM32F2, STM32F4 or STM32L1**

#### 3.Not declared

**TIM18, TIM19, TIM20, TIM21, TIM22**

#### 3. Not OK => conflict or crash

**TIM2, TIM3, TIM5, TIM6**

---
---

## From v1.2.1

Now with these new `16 ISR-based timers` (while consuming only **1 hardware timer**), the maximum interval is practically unlimited (limited only by unsigned long miliseconds). 

The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers Therefore, their executions are not blocked by bad-behaving functions / tasks.
This important feature is absolutely necessary for mission-critical tasks. 

The `ISR_16_Timers_Array_Complex` example will demonstrate the nearly perfect accuracy compared to software timers by printing the actual elapsed millisecs of each type of timers.
Being ISR-based timers, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet and Blynk services. You can also have many `(up to 16)` timers to use.
This non-being-blocked important feature is absolutely necessary for mission-critical tasks. 
You'll see software-based SimpleTimer is blocked while system is connecting to WiFi / Internet / Blynk, as well as by blocking task 
in loop(), using delay() function as an example. The elapsed time then is very unaccurate

---
---

## Usage

Before using any Timer, you have to make sure the Timer has not been used by any other purpose.

### 1. Using only Hardware Timer directly

#### 1.1 Init Hardware Timer

```
// Init timer TIM15
Portenta_H7_Timer ITimer0(TIM15);
```

#### 1.2 Set Hardware Timer Interval and attach Timer Interrupt Handler function

```
void TimerHandler0(void)
{
  // Doing something here inside ISR
}

#define TIMER0_INTERVAL_MS        1000      // 1s = 1000ms
void setup()
{
  ....
  
  // Interval in microsecs
  if (ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0))
    Serial.println("Starting  ITimer0 OK, millis() = " + String(millis()));
  else
    Serial.println("Can't set ITimer0. Select another freq. or timer");
}  
```

### 2. Using 16 ISR_based Timers from 1 Hardware Timer


#### 2.1 Init Hardware Timer and ISR-based Timer

```
// Init timer TIM16
Portenta_H7_Timer ITimer(TIM16);

// Init Portenta_H7_ISR_Timer
// Each Portenta_H7_ISR_Timer can service 16 different ISR-based timers
Portenta_H7_ISR_Timer ISR_Timer;
```

#### 2.2 Set Hardware Timer Interval and attach Timer Interrupt Handler functions

```

// In Portenta_H7, avoid doing something fancy in ISR, for example Serial.print
// Or you can get this run-time error / crash

void TimerHandler(void)
{
  ISR_Timer.run();
}

#define HW_TIMER_INTERVAL_US          100L

#define TIMER_INTERVAL_2S             2000L
#define TIMER_INTERVAL_5S             5000L
#define TIMER_INTERVAL_11S            11000L
#define TIMER_INTERVAL_101S           101000L

// In Portenta_H7, avoid doing something fancy in ISR, for example Serial.print
// Or you can get this run-time error / crash

void doingSomething2s()
{
  // Doing something here inside ISR
}
  
void doingSomething5s()
{
  // Doing something here inside ISR
}

void doingSomething11s()
{
  // Doing something here inside ISR
}

void doingSomething101s()
{
  // Doing something here inside ISR
}

void setup()
{
  ....
  
  // Interval in microsecs
  if (ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_US, TimerHandler))
  {
    lastMillis = millis();
    Serial.println("Starting  ITimer OK, millis() = " + String(lastMillis));
  }
  else
    Serial.println("Can't set ITimer correctly. Select another freq. or interval");

  // Just to demonstrate, don't use too many ISR Timers if not absolutely necessary
  // You can use up to 16 timer for each ISR_Timer
  ISR_Timer.setInterval(TIMER_INTERVAL_2S, doingSomething2s);
  ISR_Timer.setInterval(TIMER_INTERVAL_5S, doingSomething5s);
  ISR_Timer.setInterval(TIMER_INTERVAL_11S, doingSomething11s);
  ISR_Timer.setInterval(TIMER_INTERVAL_101S, doingSomething101s);
}  
```


---
---

### Examples: 

#### 1. TimerInterrupt

 1. [Argument_None](examples/Argument_None)
 2. [**Change_Interval**](examples/Change_Interval).
 3. [ISR_16_Timers_Array](examples/ISR_16_Timers_Array)
 4. [**ISR_16_Timers_Array_Complex**](examples/ISR_16_Timers_Array_Complex).
 5. [SwitchDebounce](examples/SwitchDebounce)
 6. [TimerInterruptLEDDemo](examples/TimerInterruptLEDDemo)
 7. [TimerInterruptTest](examples/TimerInterruptTest)

#### 2. Multichannel PWM
 
 8. [PWM_Multi](examples/PWM/PWM_Multi)
 9. [PWM_Multi_Args](examples/PWM/PWM_Multi_Args)
 
---
---

### Example [ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex)

```
#if !( ( defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) ) && defined(ARDUINO_ARCH_MBED) )
  #error This code is designed to run on Portenta_H7 platform! Please check your Tools->Board setting.
#endif

// These define's must be placed at the beginning before #include "Portenta_H7_TimerInterrupt.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define _TIMERINTERRUPT_LOGLEVEL_     4

#include "Portenta_H7_TimerInterrupt.h"
#include "Portenta_H7_ISR_Timer.h"

#include <SimpleTimer.h>              // https://github.com/jfturcot/SimpleTimer

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

#define HW_TIMER_INTERVAL_US      10000L

volatile uint32_t startMillis = 0;

// Depending on the board, you can select STM32H7 Hardware Timer from TIM1-TIM22
// If you select a Timer not correctly, you'll get a message from compiler
// 'TIMxx' was not declared in this scope; did you mean 'TIMyy'? 

// Portenta_H7 OK       : TIM1, TIM4, TIM7, TIM8, TIM12, TIM13, TIM14, TIM15, TIM16, TIM17
// Portenta_H7 Not OK   : TIM2, TIM3, TIM5, TIM6, TIM18, TIM19, TIM20, TIM21, TIM22
// Portenta_H7 No timer : TIM9, TIM10, TIM11. Only for STM32F2, STM32F4 and STM32L1 
// Portenta_H7 No timer : TIM18, TIM19, TIM20, TIM21, TIM22

// Init timer TIM16
Portenta_H7_Timer ITimer(TIM16);

// Init Portenta_H7_ISR_Timer
// Each Portenta_H7_ISR_Timer can service 16 different ISR-based timers
Portenta_H7_ISR_Timer ISR_Timer;


#define LED_TOGGLE_INTERVAL_MS        2000L

void TimerHandler()
{
  static bool toggle  = false;
  static int timeRun  = 0;

  ISR_Timer.run();

  // Toggle LED every LED_TOGGLE_INTERVAL_MS = 2000ms = 2s
  if (++timeRun == ((LED_TOGGLE_INTERVAL_MS * 1000) / HW_TIMER_INTERVAL_US) )
  {
    timeRun = 0;

    //timer interrupt toggles pin LED_BUILTIN
    digitalWrite(LED_BUILTIN, toggle);
    toggle = !toggle;
  }
}

/////////////////////////////////////////////////

#define NUMBER_ISR_TIMERS         16

typedef void (*irqCallback)  ();

/////////////////////////////////////////////////

#define USE_COMPLEX_STRUCT      true

#if USE_COMPLEX_STRUCT

typedef struct
{
  irqCallback   irqCallbackFunc;
  uint32_t      TimerInterval;
  unsigned long deltaMillis;
  unsigned long previousMillis;
} ISRTimerData;

// In Portenta_H7, avoid doing something fancy in ISR, for example Serial.print
// Or you can get this run-time error / crash

void doingSomething(int index);

#else

volatile unsigned long deltaMillis    [NUMBER_ISR_TIMERS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
volatile unsigned long previousMillis [NUMBER_ISR_TIMERS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// You can assign any interval for any timer here, in milliseconds
uint32_t TimerInterval[NUMBER_ISR_TIMERS] =
{
  5000L,  10000L,  15000L,  20000L,  25000L,  30000L,  35000L,  40000L,
  45000L, 50000L,  55000L,  60000L,  65000L,  70000L,  75000L,  80000L
};

void doingSomething(int index)
{
  unsigned long currentMillis  = millis();

  deltaMillis[index]    = currentMillis - previousMillis[index];
  previousMillis[index] = currentMillis;
}

#endif

////////////////////////////////////
// Shared
////////////////////////////////////

void doingSomething0()
{
  doingSomething(0);
}

void doingSomething1()
{
  doingSomething(1);
}

void doingSomething2()
{
  doingSomething(2);
}

void doingSomething3()
{
  doingSomething(3);
}

void doingSomething4()
{
  doingSomething(4);
}

void doingSomething5()
{
  doingSomething(5);
}

void doingSomething6()
{
  doingSomething(6);
}

void doingSomething7()
{
  doingSomething(7);
}

void doingSomething8()
{
  doingSomething(8);
}

void doingSomething9()
{
  doingSomething(9);
}

void doingSomething10()
{
  doingSomething(10);
}

void doingSomething11()
{
  doingSomething(11);
}

void doingSomething12()
{
  doingSomething(12);
}

void doingSomething13()
{
  doingSomething(13);
}

void doingSomething14()
{
  doingSomething(14);
}

void doingSomething15()
{
  doingSomething(15);
}

#if USE_COMPLEX_STRUCT

ISRTimerData curISRTimerData[NUMBER_ISR_TIMERS] =
{
  //irqCallbackFunc, TimerInterval, deltaMillis, previousMillis
  { doingSomething0,    5000L, 0, 0 },
  { doingSomething1,   10000L, 0, 0 },
  { doingSomething2,   15000L, 0, 0 },
  { doingSomething3,   20000L, 0, 0 },
  { doingSomething4,   25000L, 0, 0 },
  { doingSomething5,   30000L, 0, 0 },
  { doingSomething6,   35000L, 0, 0 },
  { doingSomething7,   40000L, 0, 0 },
  { doingSomething8,   45000L, 0, 0 },
  { doingSomething9,   50000L, 0, 0 },
  { doingSomething10,  55000L, 0, 0 },
  { doingSomething11,  60000L, 0, 0 },
  { doingSomething12,  65000L, 0, 0 },
  { doingSomething13,  70000L, 0, 0 },
  { doingSomething14,  75000L, 0, 0 },
  { doingSomething15,  80000L, 0, 0 }
};

void doingSomething(int index)
{
  unsigned long currentMillis  = millis();

  curISRTimerData[index].deltaMillis    = currentMillis - curISRTimerData[index].previousMillis;
  curISRTimerData[index].previousMillis = currentMillis;
}

#else

irqCallback irqCallbackFunc[NUMBER_ISR_TIMERS] =
{
  doingSomething0,  doingSomething1,  doingSomething2,  doingSomething3,
  doingSomething4,  doingSomething5,  doingSomething6,  doingSomething7,
  doingSomething8,  doingSomething9,  doingSomething10, doingSomething11,
  doingSomething12, doingSomething13, doingSomething14, doingSomething15
};

#endif
///////////////////////////////////////////

#define SIMPLE_TIMER_MS        2000L

// Init SimpleTimer
SimpleTimer simpleTimer;

// Here is software Timer, you can do somewhat fancy stuffs without many issues.
// But always avoid
// 1. Long delay() it just doing nothing and pain-without-gain wasting CPU power.Plan and design your code / strategy ahead
// 2. Very long "do", "while", "for" loops without predetermined exit time.
void simpleTimerDoingSomething2s()
{
  static unsigned long previousMillis = startMillis;

  unsigned long currMillis = millis();

  Serial.print(F("SimpleTimer : ")); Serial.print(SIMPLE_TIMER_MS / 1000);
  Serial.print(F(", ms : ")); Serial.print(currMillis);
  Serial.print(F(", Dms : ")); Serial.println(currMillis - previousMillis);

  for (uint16_t i = 0; i < NUMBER_ISR_TIMERS; i++)
  {
#if USE_COMPLEX_STRUCT
    Serial.print(F("Timer : ")); Serial.print(i);
    Serial.print(F(", programmed : ")); Serial.print(curISRTimerData[i].TimerInterval);
    Serial.print(F(", actual : ")); Serial.println(curISRTimerData[i].deltaMillis);
#else
    Serial.print(F("Timer : ")); Serial.print(i);
    Serial.print(F(", programmed : ")); Serial.print(TimerInterval[i]);
    Serial.print(F(", actual : ")); Serial.println(deltaMillis[i]);
#endif
  }

  previousMillis = currMillis;
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial);

  delay(100);

  Serial.print(F("\nStarting ISR_16_Timers_Array_Complex on ")); Serial.println(BOARD_NAME);
  Serial.println(PORTENTA_H7_TIMER_INTERRUPT_VERSION);

  // Interval in microsecs
  if (ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_US, TimerHandler))
  {
    startMillis = millis();
    Serial.print(F("Starting ITimer OK, millis() = ")); Serial.println(startMillis);
  }
  else
    Serial.println(F("Can't set ITimer correctly. Select another freq. or interval"));

  // Just to demonstrate, don't use too many ISR Timers if not absolutely necessary
  // You can use up to 16 timer for each Portenta_H7_ISR_Timer
  for (uint16_t i = 0; i < NUMBER_ISR_TIMERS; i++)
  {
#if USE_COMPLEX_STRUCT
    curISRTimerData[i].previousMillis = startMillis;
    ISR_Timer.setInterval(curISRTimerData[i].TimerInterval, curISRTimerData[i].irqCallbackFunc);
#else
    previousMillis[i] = startMillis;
    ISR_Timer.setInterval(TimerInterval[i], irqCallbackFunc[i]);
#endif
  }

  // You need this timer for non-critical tasks. Avoid abusing ISR if not absolutely necessary.
  simpleTimer.setInterval(SIMPLE_TIMER_MS, simpleTimerDoingSomething2s);
}

#define BLOCKING_TIME_MS      10000L

void loop()
{
  // This unadvised blocking task is used to demonstrate the blocking effects onto the execution and accuracy to Software timer
  // You see the time elapse of ISR_Timer still accurate, whereas very unaccurate for Software Timer
  // The time elapse for 2000ms software timer now becomes 3000ms (BLOCKING_TIME_MS)
  // While that of ISR_Timer is still prefect.
  delay(BLOCKING_TIME_MS);

  // You need this Software timer for non-critical tasks. Avoid abusing ISR if not absolutely necessary
  // You don't need to and never call ISR_Timer.run() here in the loop(). It's already handled by ISR timer.
  simpleTimer.run();
}
```
---
---

### Debug Terminal Output Samples

### 1. ISR_16_Timers_Array_Complex on PORTENTA_H7_M7

The following is the sample terminal output when running example [ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex) on **Portenta_H7** to demonstrate the accuracy of ISR Hardware Timer, **especially when system is very busy**.  The ISR timer is **programmed for 2s, is activated exactly after 2.000s !!!**

While software-based `SimpleTimer`, **programmed for 2s, is activated after 10.000s !!!**.

In this example, 16 independent ISR Timers are used, yet utilized just one Hardware Timer. The Timer Intervals and Function Pointers are stored in arrays to facilitate the code modification.


```
Starting ISR_16_Timers_Array_Complex on PORTENTA_H7_M7
Portenta_H7_TimerInterrupt v1.3.0
[TISR] Portenta_H7_TimerInterrupt: Timer Input Freq (Hz) = 200000000
[TISR] Frequency = 1000000.00 , _count = 10000
Starting ITimer OK, millis() = 1111
SimpleTimer : 2, ms : 11111, Dms : 10000
Timer : 0, programmed : 5000, actual : 5004
Timer : 1, programmed : 10000, actual : 0
Timer : 2, programmed : 15000, actual : 0
Timer : 3, programmed : 20000, actual : 0
Timer : 4, programmed : 25000, actual : 0
Timer : 5, programmed : 30000, actual : 0
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2, ms : 21114, Dms : 10003
Timer : 0, programmed : 5000, actual : 4994
Timer : 1, programmed : 10000, actual : 10008
Timer : 2, programmed : 15000, actual : 15002
Timer : 3, programmed : 20000, actual : 0
Timer : 4, programmed : 25000, actual : 0
Timer : 5, programmed : 30000, actual : 0
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2, ms : 31117, Dms : 10003
Timer : 0, programmed : 5000, actual : 5005
Timer : 1, programmed : 10000, actual : 9999
Timer : 2, programmed : 15000, actual : 15003
Timer : 3, programmed : 20000, actual : 20006
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30005
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2, ms : 41120, Dms : 10003
Timer : 0, programmed : 5000, actual : 4994
Timer : 1, programmed : 10000, actual : 9998
Timer : 2, programmed : 15000, actual : 15003
Timer : 3, programmed : 20000, actual : 19997
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30005
Timer : 6, programmed : 35000, actual : 35009
Timer : 7, programmed : 40000, actual : 40003
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2, ms : 51123, Dms : 10003
Timer : 0, programmed : 5000, actual : 4995
Timer : 1, programmed : 10000, actual : 9999
Timer : 2, programmed : 15000, actual : 15002
Timer : 3, programmed : 20000, actual : 19997
Timer : 4, programmed : 25000, actual : 25002
Timer : 5, programmed : 30000, actual : 30005
Timer : 6, programmed : 35000, actual : 35009
Timer : 7, programmed : 40000, actual : 40003
Timer : 8, programmed : 45000, actual : 45007
Timer : 9, programmed : 50000, actual : 50002
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2, ms : 61126, Dms : 10003
Timer : 0, programmed : 5000, actual : 4994
Timer : 1, programmed : 10000, actual : 9998
Timer : 2, programmed : 15000, actual : 14993
Timer : 3, programmed : 20000, actual : 19997
Timer : 4, programmed : 25000, actual : 25002
Timer : 5, programmed : 30000, actual : 29995
Timer : 6, programmed : 35000, actual : 35009
Timer : 7, programmed : 40000, actual : 40003
Timer : 8, programmed : 45000, actual : 45007
Timer : 9, programmed : 50000, actual : 50002
Timer : 10, programmed : 55000, actual : 55006
Timer : 11, programmed : 60000, actual : 60000
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2, ms : 71129, Dms : 10003
Timer : 0, programmed : 5000, actual : 5005
Timer : 1, programmed : 10000, actual : 10009
Timer : 2, programmed : 15000, actual : 14993
Timer : 3, programmed : 20000, actual : 19997
Timer : 4, programmed : 25000, actual : 25002
Timer : 5, programmed : 30000, actual : 29995
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40003
Timer : 8, programmed : 45000, actual : 45007
Timer : 9, programmed : 50000, actual : 50002
Timer : 10, programmed : 55000, actual : 55006
Timer : 11, programmed : 60000, actual : 60000
Timer : 12, programmed : 65000, actual : 65004
Timer : 13, programmed : 70000, actual : 70009
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2, ms : 81132, Dms : 10003
Timer : 0, programmed : 5000, actual : 5005
Timer : 1, programmed : 10000, actual : 9999
Timer : 2, programmed : 15000, actual : 15003
Timer : 3, programmed : 20000, actual : 20008
Timer : 4, programmed : 25000, actual : 25001
Timer : 5, programmed : 30000, actual : 29995
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40005
Timer : 8, programmed : 45000, actual : 45007
Timer : 9, programmed : 50000, actual : 50002
Timer : 10, programmed : 55000, actual : 55006
Timer : 11, programmed : 60000, actual : 60000
Timer : 12, programmed : 65000, actual : 65004
Timer : 13, programmed : 70000, actual : 70009
Timer : 14, programmed : 75000, actual : 75003
Timer : 15, programmed : 80000, actual : 80008
```

---

### 2. TimerInterruptTest on PORTENTA_H7_M7

The following is the sample terminal output when running example [**TimerInterruptTest**](examples/TimerInterruptTest) on **Portenta_H7** to demonstrate how to start/stop Hardware Timers.

```
Starting TimerInterruptTest on PORTENTA_H7_M7
Portenta_H7_TimerInterrupt v1.3.0
[TISR] Portenta_H7_TimerInterrupt: Timer Input Freq (Hz) = 200000000
[TISR] Frequency = 1000000.00 , _count = 1000000
Starting ITimer0 OK, millis() = 1410
[TISR] Portenta_H7_TimerInterrupt: Timer Input Freq (Hz) = 200000000
[TISR] Frequency = 1000000.00 , _count = 3000000
Starting  ITimer1 OK, millis() = 1411
Stop ITimer0, millis() = 10001
Start ITimer0, millis() = 20002
Stop ITimer1, millis() = 30001
Stop ITimer0, millis() = 30003
Start ITimer0, millis() = 40004
Stop ITimer0, millis() = 50005
Start ITimer1, millis() = 60002
Start ITimer0, millis() = 60006
Stop ITimer0, millis() = 70007
```

---

### 3. Argument_None on PORTENTA_H7_M7

The following is the sample terminal output when running example [**Argument_None**](examples/Argument_None) on **Portenta_H7** to demonstrate how to use Multiple Hardware Timers.

```
Starting Argument_None on PORTENTA_H7_M7
Portenta_H7_TimerInterrupt v1.3.0
[TISR] Portenta_H7_TimerInterrupt: Timer Input Freq (Hz) = 100000000
[TISR] Frequency = 1000000.00 , _count = 1000000
Starting ITimer0 OK, millis() = 1009
[TISR] Portenta_H7_TimerInterrupt: Timer Input Freq (Hz) = 100000000
[TISR] Frequency = 1000000.00 , _count = 2000000
Starting  ITimer1 OK, millis() = 1010
[TISR] Portenta_H7_TimerInterrupt: Timer Input Freq (Hz) = 100000000
[TISR] Frequency = 1000000.00 , _count = 5000000
Starting  ITimer2 OK, millis() = 1010
```

---

### 4. Change_Interval on PORTENTA_H7_M7

The following is the sample terminal output when running example [Change_Interval](examples/Change_Interval) on **Portenta_H7** to demonstrate how to change Timer Interval on-the-fly

```
Starting Change_Interval on PORTENTA_H7_M7
Portenta_H7_TimerInterrupt v1.3.0
[TISR] Portenta_H7_TimerInterrupt: Timer Input Freq (Hz) = 200000000
[TISR] Frequency = 1000000.00 , _count = 500000
Starting  Timer0 OK, millis() = 1415
[TISR] Portenta_H7_TimerInterrupt: Timer Input Freq (Hz) = 200000000
[TISR] Frequency = 1000000.00 , _count = 1000000
Starting ITimer1 OK, millis() = 1416
Time = 10001, Timer0Count = 18, Timer1Count = 9
Time = 20002, Timer0Count = 37, Timer1Count = 19
[TISR] Portenta_H7_TimerInterrupt: Timer Input Freq (Hz) = 200000000
[TISR] Frequency = 1000000.00 , _count = 1000000
[TISR] Portenta_H7_TimerInterrupt: Timer Input Freq (Hz) = 200000000
[TISR] Frequency = 1000000.00 , _count = 2000000
Changing Interval, Timer0 = 1000,  Timer1 = 2000
Time = 30003, Timer0Count = 47, Timer1Count = 24
Time = 40004, Timer0Count = 57, Timer1Count = 29
[TISR] Portenta_H7_TimerInterrupt: Timer Input Freq (Hz) = 200000000
[TISR] Frequency = 1000000.00 , _count = 500000
[TISR] Portenta_H7_TimerInterrupt: Timer Input Freq (Hz) = 200000000
[TISR] Frequency = 1000000.00 , _count = 1000000
Changing Interval, Timer0 = 500,  Timer1 = 1000
Time = 50005, Timer0Count = 75, Timer1Count = 37
Time = 60006, Timer0Count = 95, Timer1Count = 47
[TISR] Portenta_H7_TimerInterrupt: Timer Input Freq (Hz) = 200000000
[TISR] Frequency = 1000000.00 , _count = 1000000
[TISR] Portenta_H7_TimerInterrupt: Timer Input Freq (Hz) = 200000000
[TISR] Frequency = 1000000.00 , _count = 2000000
```

---

### 5. ISR_16_Timers_Array on PORTENTA_H7_M7

The following is the sample terminal output when running new example [ISR_16_Timers_Array](examples/ISR_16_Timers_Array) on **Portenta_H7** to demonstrate the accuracy of ISR Hardware Timer, **especially when system is very busy or blocked**. The 16 independent ISR timers are **programmed to be activated repetitively after certain intervals, is activated exactly after that programmed interval !!!**

While software-based `SimpleTimer`, **programmed for 2s, is activated after 10.000s in loop()!!!**.


```
Starting ISR_16_Timers_Array on PORTENTA_H7_M7
Portenta_H7_TimerInterrupt v1.3.0
[TISR] Portenta_H7_TimerInterrupt: Timer Input Freq (Hz) = 200000000
[TISR] Frequency = 1000000.00 , _count = 100
Starting ITimer OK, millis() = 1109
simpleTimerDoingSomething2s: Delta programmed ms = 2000, actual = 10000
Timer : 0, programmed : 1000, actual : 1000
Timer : 1, programmed : 2000, actual : 2000
Timer : 2, programmed : 3000, actual : 3000
Timer : 3, programmed : 4000, actual : 4000
Timer : 4, programmed : 5000, actual : 5000
Timer : 5, programmed : 6000, actual : 6000
Timer : 6, programmed : 7000, actual : 7000
Timer : 7, programmed : 8000, actual : 8000
Timer : 8, programmed : 9000, actual : 9000
Timer : 9, programmed : 10000, actual : 10000
Timer : 10, programmed : 11000, actual : 0
Timer : 11, programmed : 12000, actual : 0
Timer : 12, programmed : 13000, actual : 0
Timer : 13, programmed : 14000, actual : 0
Timer : 14, programmed : 15000, actual : 0
Timer : 15, programmed : 16000, actual : 0
simpleTimerDoingSomething2s: Delta programmed ms = 2000, actual = 10000
Timer : 0, programmed : 1000, actual : 1000
Timer : 1, programmed : 2000, actual : 2000
Timer : 2, programmed : 3000, actual : 3000
Timer : 3, programmed : 4000, actual : 4000
Timer : 4, programmed : 5000, actual : 5000
Timer : 5, programmed : 6000, actual : 6000
Timer : 6, programmed : 7000, actual : 7000
Timer : 7, programmed : 8000, actual : 8000
Timer : 8, programmed : 9000, actual : 9000
Timer : 9, programmed : 10000, actual : 10000
Timer : 10, programmed : 11000, actual : 11000
Timer : 11, programmed : 12000, actual : 12000
Timer : 12, programmed : 13000, actual : 13000
Timer : 13, programmed : 14000, actual : 14000
Timer : 14, programmed : 15000, actual : 15000
Timer : 15, programmed : 16000, actual : 16000
simpleTimerDoingSomething2s: Delta programmed ms = 2000, actual = 10001
Timer : 0, programmed : 1000, actual : 1000
Timer : 1, programmed : 2000, actual : 2000
Timer : 2, programmed : 3000, actual : 3000
Timer : 3, programmed : 4000, actual : 4000
Timer : 4, programmed : 5000, actual : 5000
Timer : 5, programmed : 6000, actual : 6000
Timer : 6, programmed : 7000, actual : 7000
Timer : 7, programmed : 8000, actual : 8000
Timer : 8, programmed : 9000, actual : 9000
Timer : 9, programmed : 10000, actual : 10000
Timer : 10, programmed : 11000, actual : 11000
Timer : 11, programmed : 12000, actual : 12000
Timer : 12, programmed : 13000, actual : 13000
Timer : 13, programmed : 14000, actual : 14000
Timer : 14, programmed : 15000, actual : 15000
Timer : 15, programmed : 16000, actual : 16000
```

---

### 6. PWM_Multi_Args on PORTENTA_H7_M7

The following is the sample terminal output when running new example [PWM_Multi_Args](examples/PWM/PWM_Multi_Args) on **Portenta_H7** to demonstrate the usage of multichannel PWM using multiple Hardware Timers. The 6 independent Hardware Timers are used **to control 6 different PWM outputs**, with totally independent frequencies and dutycycles.


```
Starting PWM_Multi_Args on PORTENTA_H7_M7
Portenta_H7_TimerInterrupt v1.3.0
Index = 0, Instance = 0x40010000, channel = 3, TimerIndex = 0
Index = 1, Instance = 0x40000800, channel = 1, TimerIndex = 3
Index = 2, Instance = 0x40001400, channel = 2, TimerIndex = 6
Index = 3, Instance = 0x40010400, channel = 2, TimerIndex = 7
Index = 4, Instance = 0x40001800, channel = 1, TimerIndex = 8
Index = 5, Instance = 0x40001C00, channel = 3, TimerIndex = 9
Index = 6, Instance = 0x40002000, channel = 1, TimerIndex = 10

==========================================================================================================
Count 0		Count 1		Count 2		Count 3		Count 4		Count 5		Count 6		
==========================================================================================================
10		    20		    50		    100		    199		    498		    995		
20		    40		    100		    199		    398		    995		    1990		
30		    60		    150		    299		    597		    1493		  2985		
40		    80		    199		    398		    796		    1990		  3980		
50		    100		    249		    498		    995		    2488		  4975		
60		    120		    299		    597		    1194		  2985		  5970		
70		    140		    349		    697		    1393		  3483		  6965		
80		    160		    398		    796		    1592		  3980		  7960		
90		    180		    448		    896		    1791		  4478		  8955		
100		    199		    498		    995		    1990		  4975		  9950		
110		    219		    548		    1095		  2189		  5473		  10945		
120		    239		    597		    1194		  2388		  5970		  11940		
130		    259		    647		    1294		  2587		  6468		  12935		
140		    279		    697		    1393		  2786		  6965		  13930		
150		    299		    747		    1493		  2985		  7463		  14925		
160		    319		    796		    1592		  3184		  7960		  15920		
170		    339		    846		    1692		  3383		  8458		  16915		
180		    359		    896		    1791		  3582		  8955		  17910		
190		    379		    946		    1891		  3781		  9453		  18905		
199		    398		    995		    1990		  3980		  9950		  19900		
```

---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level (_TIMERINTERRUPT_LOGLEVEL_) from 0 to 4

```cpp
// These define's must be placed at the beginning before #include "Portenta_H7_TimerInterrupt.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define _TIMERINTERRUPT_LOGLEVEL_     0
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.


---
---

### Issues

Submit issues to: [Portenta_H7_TimerInterrupt issues](https://github.com/khoih-prog/Portenta_H7_TimerInterrupt/issues)

---

## TO DO

1. Search for bug and improvement.
2. Similar features for remaining Arduino boards such as SAM-DUE

---

## DONE

1. Basic hardware timers for **Portenta_H7**.
2. More hardware-initiated software-enabled timers
3. Longer time interval
4. Add Table of Contents

---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.


---

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/Portenta_H7_TimerInterrupt/blob/master/LICENSE)

---

## Copyright

Copyright 2021- Khoi Hoang


