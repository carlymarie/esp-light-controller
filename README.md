# Lighting Controller
Remove `.example` from `platformio.ini.example` and `lib/CORE/configuration.h.example` and make changes to the files as needed

## Disclaimer
- ESP32 is untested
- RTC support hasn't been coded but it has a clock
- Scheduled timer and clock resets if the device loses power or restarts
- LED Controller module untested

## First Compile WILL FAIL
On Windows the first compile will fail make the following changes

## For ESP8266

Rename `.pio/libdeps/nodemcuv2/Time_ID44/Time.h` to `.pio/libdeps/nodemcuv2/Time_ID44/_Time.h`

## For ESP32

Rename `.pio/libdeps/esp32/Time_ID44/Time.h` to `.pio/libdeps/esp32/Time_ID44/_Time.h`

## Finally
Change `#include "Time.h"` to `#include "_Time.h"` in `DateString.cpp` and `Time.cpp`