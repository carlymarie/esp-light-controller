#ifndef _LIGHT_H_
#define _LIGHT_H_
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>
#include "configuration.h"
class LIGHT
{
public:
    void setup();
    void setBrightness(uint8_t, uint8_t);
    void on(uint8_t);
    void off(uint8_t);
    bool state(uint8_t);

private:
    Adafruit_PWMServoDriver *pwm;
    uint8_t lights[LED_COUNT];
};
extern LIGHT *led;
#endif // _LIGHT_H_