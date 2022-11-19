# Portenta_H7_TimerInterrupt Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/Portenta_H7_TimerInterrupt.svg?)](https://www.ardu-badge.com/Portenta_H7_TimerInterrupt)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Portenta_H7_TimerInterrupt.svg)](https://github.com/khoih-prog/Portenta_H7_TimerInterrupt/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/Portenta_H7_TimerInterrupt/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Portenta_H7_TimerInterrupt.svg)](http://github.com/khoih-prog/Portenta_H7_TimerInterrupt/issues)


<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>
<a href="https://profile-counter.glitch.me/khoih-prog/count.svg" title="Total khoih-prog Visitor count"><img src="https://profile-counter.glitch.me/khoih-prog/count.svg" style="height: 30px;width: 200px;"></a>
<a href="https://profile-counter.glitch.me/khoih-prog-Portenta_H7_TimerInterrupt/count.svg" title="Portenta_H7_TimerInterrupt Visitor count"><img src="https://profile-counter.glitch.me/khoih-prog-Portenta_H7_TimerInterrupt/count.svg" style="height: 30px;width: 200px;"></a>


---
---

## Table of Contents

* [Important Change from v1.4.0](#Important-Change-from-v140)
* [Why do we need this Portenta_H7_TimerInterrupt library](#why-do-we-need-this-Portenta_H7_TimerInterrupt-library)
  * [Features](#features)
  * [Why using ISR-based Hardware Timer Interrupt is better](#why-using-isr-based-hardware-timer-interrupt-is-better)
  * [Currently supported Boards](#currently-supported-boards)
  * [Important Notes about ISR](#important-notes-about-isr)
* [Changelog](changelog.md) 
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
    * [ 8. **multiFileProject**](examples/multiFileProject) **New**
  * [2. Multichannel PWM](#2-Multichannel-PWM) 
    * [ 9. PWM_Multi](examples/PWM/PWM_Multi)
    * [10. PWM_Multi_Args](examples/PWM/PWM_Multi_Args)
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

### Important Change from v1.4.0

Please have a look at [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)

### Why do we need this [Portenta_H7_TimerInterrupt library](https://github.com/khoih-prog/Portenta_H7_TimerInterrupt)

### Features

This library enables you to use Interrupt from Hardware Timers on an **STM32H7-based Portenta_H7** board. 

As **Hardware Timers are rare, and very precious assets** of any board, this library now enables you to use up to **16 ISR-based Timers, while consuming only 1 Hardware Timer**. Timers' interval is very long (**ulong millisecs**).

Now with these new **16 ISR-based timers**, the maximum interval is **practically unlimited** (limited only by unsigned long milliseconds) while **the accuracy is nearly perfect** compared to software timers. 

The most important feature is they're ISR-based timers. Therefore, their executions are **not blocked by bad-behaving functions / tasks**. This important feature is absolutely necessary for mission-critical tasks. 

The [**ISR_16_Timers_Array_Complex**](examples/ISR_16_Timers_Array_Complex) example will demonstrate the nearly perfect accuracy compared to software timers by printing the actual elapsed millisecs of each type of timers.

The [**PWM_Multi_Args**](examples/PWM/PWM_Multi_Args) will demonstrate the usage of multichannel PWM using multiple Hardware Timers. The 6 independent Hardware Timers are used **to control 6 different PWM outputs**, with totally independent frequencies and dutycycles.

Being ISR-based timers, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet or Blynk services. You can also have many `(up to 16)` timers to use.

This non-being-blocked important feature is absolutely necessary for mission-critical tasks.

You'll see blynkTimer Software is blocked while system is connecting to WiFi / Internet / Blynk, as well as by blocking task 
in `loop()`, using delay() function as an example. The elapsed time then is very unaccurate

### Why using ISR-based Hardware Timer Interrupt is better

Imagine you have a system with a **mission-critical** function, measuring water level and control the sump pump or doing something much more important. You normally use a software timer to poll, or even place the function in `loop()`. But what if another function is **blocking** the `loop()` or `setup()`.

So your function **might not be executed, and the result would be disastrous.**

You'd prefer to have your function called, no matter what happening with other functions (busy loop, bug, etc.).

The correct choice is to use a Hardware Timer with **Interrupt** to call your function.

These hardware timers, using interrupt, still work even if other functions are blocking. Moreover, they are much more **precise** (certainly depending on clock frequency accuracy) than other software timers using `millis()` or `micros()`. That's necessary if you need to measure some data requiring better accuracy.

Functions using normal software timers, relying on `loop()` and calling `millis()`, won't work if the `loop()` or `setup()` is blocked by certain operation. For example, certain function is blocking while it's connecting to WiFi or some services.

The catch is **your function is now part of an ISR (Interrupt Service Routine), and must be lean / mean, and follow certain rules.** More to read on:

[**HOWTO Attach Interrupt**](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)

---

### Currently supported Boards

1. **Portenta_H7 boards** such as Portenta_H7 Rev2 ABX00042, etc., using [**ArduinoCore mbed_portenta** core](https://github.com/arduino/ArduinoCore-mbed)

---

#### Important Notes about ISR

1. Inside the attached function, **delay() won’t work and the value returned by millis() will not increment.** Serial data received while in the function may be lost. You should declare as **volatile any variables that you modify within the attached function.**

2. Typically global variables are used to pass data between an ISR and the main program. To make sure variables shared between an ISR and the main program are updated correctly, declare them as volatile.

---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`ArduinoCore-mbed mbed_portenta core 3.4.1+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino **Portenta_H7** boards, such as **Portenta_H7 Rev2 ABX00042, etc.**. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)
 3. To use with certain example, depending on which Ethernet card you're using:
   - [`Ethernet_Generic library v2.7.1+`](https://github.com/khoih-prog/Ethernet_Generic) for W5100, W5200 and W5500.  [![GitHub release](https://img.shields.io/github/release/khoih-prog/Ethernet_Generic.svg)](https://github.com/khoih-prog/Ethernet_Generic/releases/latest)
   - [`EthernetENC library v2.0.3+`](https://github.com/jandrassy/EthernetENC) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/jandrassy/EthernetENC.svg)](https://github.com/jandrassy/EthernetENC/releases/latest). **New and Better**
   - [`UIPEthernet library v2.0.12+`](https://github.com/UIPEthernet/UIPEthernet) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/UIPEthernet/UIPEthernet.svg)](https://github.com/UIPEthernet/UIPEthernet/releases/latest)
 4. To use with certain example
   - [`SimpleTimer library`](https://github.com/jfturcot/SimpleTimer) for [ISR_16_Timers_Array](examples/ISR_16_Timers_Array) and [ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex) examples.
   
   
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
3. Install [**Portenta_H7_TimerInterrupt** library](https://registry.platformio.org/libraries/khoih-prog/Portenta_H7_TimerInterrupt) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/Portenta_H7_TimerInterrupt/installation). Search for **Portenta_H7_TimerInterrupt** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For Portenta_H7 boards using Arduino IDE in Linux

  **To be able to upload firmware to Portenta_H7 using Arduino IDE in Linux (Ubuntu, etc.)**, you have to copy the file [portenta_post_install.sh](Packages_Patches/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh) into mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh). 
  
  Then run the following command using `sudo`
  
```
$ cd ~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1
$ chmod 755 portenta_post_install.sh
$ sudo ./portenta_post_install.sh
```

This will create the file `/etc/udev/rules.d/49-portenta_h7.rules` as follows:

```
# Portenta H7 bootloader mode UDEV rules

SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="035b", GROUP="plugdev", MODE="0666"
```

Supposing the ArduinoCore-mbed core version is 3.4.1. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/x.yy.zz/portenta_post_install.sh`

---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can include these `.hpp` or `.h` files

```cpp
// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "Portenta_H7_TimerInterrupt.h"     //https://github.com/khoih-prog/Portenta_H7_TimerInterrupt

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "Portenta_H7_ISR_Timer.hpp"         //https://github.com/khoih-prog/Portenta_H7_TimerInterrupt
```

in many files. But be sure to use the following `.h` file **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```cpp
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "Portenta_H7_ISR_Timer.h"           //https://github.com/khoih-prog/Portenta_H7_TimerInterrupt
```

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

```cpp
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

```cpp
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

Now with these new `16 ISR-based timers` (while consuming only **1 hardware timer**), the maximum interval is practically unlimited (limited only by unsigned long milliseconds). 

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

```cpp
// Init timer TIM15
Portenta_H7_Timer ITimer0(TIM15);
```

#### 1.2 Set Hardware Timer Interval and attach Timer Interrupt Handler function

```cpp
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

```cpp
// Init timer TIM16
Portenta_H7_Timer ITimer(TIM16);

// Init Portenta_H7_ISR_Timer
// Each Portenta_H7_ISR_Timer can service 16 different ISR-based timers
Portenta_H7_ISR_Timer ISR_Timer;
```

#### 2.2 Set Hardware Timer Interval and attach Timer Interrupt Handler functions

```cpp

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
 8. [**multiFileProject**](examples/multiFileProject). **New**


#### 2. Multichannel PWM
 
 9. [PWM_Multi](examples/PWM/PWM_Multi)
10. [PWM_Multi_Args](examples/PWM/PWM_Multi_Args)
 
---
---

### Example [ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex)

https://github.com/khoih-prog/Portenta_H7_TimerInterrupt/blob/63d489168658f7eb3ea0f5373306865475283523/examples/ISR_16_Timers_Array_Complex/ISR_16_Timers_Array_Complex.ino#L35-L369


---
---

### Debug Terminal Output Samples

### 1. ISR_16_Timers_Array_Complex on PORTENTA_H7_M7

The following is the sample terminal output when running example [ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex) on **Portenta_H7** to demonstrate the accuracy of ISR Hardware Timer, **especially when system is very busy**.  The ISR timer is **programmed for 2s, is activated exactly after 2.000s !!!**

While software-based `SimpleTimer`, **programmed for 2s, is activated after 10.000s !!!**.

In this example, 16 independent ISR Timers are used, yet utilized just one Hardware Timer. The Timer Intervals and Function Pointers are stored in arrays to facilitate the code modification.


```
Starting ISR_16_Timers_Array_Complex on PORTENTA_H7_M7
Portenta_H7_TimerInterrupt v1.4.0
[TISR] Timer Input Freq (Hz) = 200000000
[TISR] Frequency =100.00, _count = 10000
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
Portenta_H7_TimerInterrupt v1.4.0
[TISR] Timer Input Freq (Hz) = 200000000
[TISR] Frequency =1.00, _count = 1000000
Starting ITimer0 OK, millis() = 980
[TISR] Timer Input Freq (Hz) = 200000000
[TISR] Frequency =0.33, _count = 3000000
Starting  ITimer1 OK, millis() = 980
Stop ITimer0, millis() = 10001
Start ITimer0, millis() = 20002
Stop ITimer1, millis() = 30001
Stop ITimer0, millis() = 30003
Start ITimer0, millis() = 40004
```

---

### 3. Argument_None on PORTENTA_H7_M7

The following is the sample terminal output when running example [**Argument_None**](examples/Argument_None) on **Portenta_H7** to demonstrate how to use Multiple Hardware Timers.

```
Starting Argument_None on PORTENTA_H7_M7
Portenta_H7_TimerInterrupt v1.4.0
[TISR] Timer Input Freq (Hz) = 200000000
[TISR] Frequency =1.00, _count = 1000000
Starting ITimer0 OK, millis() = 1259
[TISR] Timer Input Freq (Hz) = 200000000
[TISR] Frequency =0.50, _count = 2000000
Starting  ITimer1 OK, millis() = 1259
[TISR] Timer Input Freq (Hz) = 200000000
[TISR] Frequency =0.20, _count = 5000000
Starting  ITimer2 OK, millis() = 1260
```

---

### 4. Change_Interval on PORTENTA_H7_M7

The following is the sample terminal output when running example [Change_Interval](examples/Change_Interval) on **Portenta_H7** to demonstrate how to change Timer Interval on-the-fly

```
Starting Change_Interval on PORTENTA_H7_M7
Portenta_H7_TimerInterrupt v1.4.0
[TISR] Timer Input Freq (Hz) = 200000000
[TISR] Frequency =2.00, _count = 500000
Starting  Timer0 OK, millis() = 1011
[TISR] Timer Input Freq (Hz) = 200000000
[TISR] Frequency =1.00, _count = 1000000
Starting ITimer1 OK, millis() = 1011
Time = 10001, Timer0Count = 18, Timer1Count = 9
Time = 20002, Timer0Count = 38, Timer1Count = 19
[TISR] Timer Input Freq (Hz) = 200000000
[TISR] Frequency =1.00, _count = 1000000
[TISR] Timer Input Freq (Hz) = 200000000
[TISR] Frequency =0.50, _count = 2000000
Changing Interval, Timer0 = 1000,  Timer1 = 2000
Time = 30003, Timer0Count = 48, Timer1Count = 24
Time = 40004, Timer0Count = 58, Timer1Count = 29
[TISR] Timer Input Freq (Hz) = 200000000
[TISR] Frequency =2.00, _count = 500000
[TISR] Timer Input Freq (Hz) = 200000000
[TISR] Frequency =1.00, _count = 1000000
Changing Interval, Timer0 = 500,  Timer1 = 1000
Time = 50005, Timer0Count = 76, Timer1Count = 37
Time = 60006, Timer0Count = 96, Timer1Count = 47
[TISR] Timer Input Freq (Hz) = 200000000
[TISR] Frequency =1.00, _count = 1000000
[TISR] Timer Input Freq (Hz) = 200000000
[TISR] Frequency =0.50, _count = 2000000
Changing Interval, Timer0 = 1000,  Timer1 = 2000
```

---

### 5. ISR_16_Timers_Array on PORTENTA_H7_M7

The following is the sample terminal output when running new example [ISR_16_Timers_Array](examples/ISR_16_Timers_Array) on **Portenta_H7** to demonstrate the accuracy of ISR Hardware Timer, **especially when system is very busy or blocked**. The 16 independent ISR timers are **programmed to be activated repetitively after certain intervals, is activated exactly after that programmed interval !!!**

While software-based `SimpleTimer`, **programmed for 2s, is activated after 10.000s in loop()!!!**.


```
Starting ISR_16_Timers_Array on PORTENTA_H7_M7
Portenta_H7_TimerInterrupt v1.4.0
[TISR] Timer Input Freq (Hz) = 200000000
[TISR] Frequency =10000.00, _count = 100
Starting ITimer OK, millis() = 1009
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
Portenta_H7_TimerInterrupt v1.4.0
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
10		20		50		100		199		497		994		
20		40		100		199		398		994		1988		
30		60		150		299		597		1491		2982		
40		80		199		398		796		1988		3976		
50		100		249		498		995		2486		4971		
60		120		299		597		1193		2983		5965		
70		140		348		696		1392		3480		6959		
80		160		398		796		1591		3977		7953		
90		179		448		895		1790		4474		8947		
100		199		498		995		1989		4971		9941		
110		219		547		1094		2188		5468		10935		
120		239		597		1193		2386		5965		11930		
130		259		647		1293		2585		6462		12924		
140		279		696		1392		2784		6959		13918		
150		299		746		1492		2983		7456		14912		
160		319		796		1591		3182		7953		15906		
170		339		845		1690		3380		8450		16900			
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
5. Fix `multiple-definitions` linker error
6. Optimize library code by using `reference-passing` instead of `value-passing`

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

Copyright (c) 2021- Khoi Hoang


