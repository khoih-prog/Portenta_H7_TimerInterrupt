# Portenta_H7_TimerInterrupt Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/Portenta_H7_TimerInterrupt.svg?)](https://www.ardu-badge.com/Portenta_H7_TimerInterrupt)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Portenta_H7_TimerInterrupt.svg)](https://github.com/khoih-prog/Portenta_H7_TimerInterrupt/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/Portenta_H7_TimerInterrupt/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Portenta_H7_TimerInterrupt.svg)](http://github.com/khoih-prog/Portenta_H7_TimerInterrupt/issues)


<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>


---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v1.4.0](#Releases-v140)
  * [Releases v1.3.1](#Releases-v131)
  * [Releases v1.3.0](#Releases-v130)
  * [Initial Releases v1.2.1](#Initial-Releases-v121)

---
---

## Changelog

### Releases v1.4.0

1. Fix `multiple-definitions` linker error. Drop `src_cpp` and `src_h` directories
2. Add example [multiFileProject](examples/multiFileProject) to demo for multiple-file project.
3. Fix `reattachInterrupt()` bug. Check [bugfix: reattachInterrupt() pass wrong frequency value to setFrequency() #19](https://github.com/khoih-prog/ESP8266TimerInterrupt/pull/19)
4. Optimize library code by using `reference-passing` instead of `value-passing`
5. Update all examples
6. Update `Packages_Patches`

### Releases v1.3.1

1. Fix warnings in PWM examples

### Releases v1.3.0

1. Add PWM features and examples

### Initial Releases v1.2.1

1. Initial coding to support **Portenta_H7 boards** such as Portenta_H7 Rev2 ABX00042, etc., using [**ArduinoCore-mbed mbed_portenta** core](https://github.com/arduino/ArduinoCore-mbed)
2. Permit up to 16 super-long-time, super-accurate ISR-based timers to avoid being blocked
3. Using cpp code besides Impl.h code to use if Multiple-Definition linker error.
4. Bump version to v1.2.1 to sync with [STM32_TimerInterrupt library](https://github.com/khoih-prog/STM32_TimerInterrupt)

