#include "light.h"

void LIGHT::setup()
{
    pwm = new Adafruit_PWMServoDriver();
    pwm->begin();
    pwm->setPWMFreq(1600); // This is the maximum PWM frequency
    
    // Turn off all lights
    for (uint8_t i = 0; i < LED_COUNT; i++)
    {
        lights[i] = 0;
        off(i);
    }
}

void LIGHT::on(uint8_t _pin)
{
    pwm->setPWM(_pin, 4096, 0);
    lights[_pin] = 1;
}
void LIGHT::off(uint8_t _pin)
{
    pwm->setPWM(_pin, 0, 4096);
    lights[_pin] = 0;
}
bool LIGHT::state(uint8_t _pin)
{
    return lights[_pin];
}