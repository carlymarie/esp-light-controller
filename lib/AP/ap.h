#ifndef _AP_H_
#define _AP_H_
#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

#include "configuration.h"
class AP
{
public:
    void setup();
};
#endif // _AP_H_