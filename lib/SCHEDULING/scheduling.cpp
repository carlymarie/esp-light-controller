#include "scheduling.h"
void SCHEDULING::setEpoch(uint8_t _h, uint8_t _m, uint8_t _s, uint8_t _d, uint8_t _mo, uint16_t _y)
{
    setTime(_h, _m, _s, _d, _mo, _y);
}
void SCHEDULING::setOnTime(uint8_t _hour, uint8_t _minute)
{
    ontime.hour = _hour;
    ontime.minute = _minute;
}
void SCHEDULING::setOffTime(uint8_t _hour, uint8_t _minute)
{
    offtime.hour = _hour;
    offtime.minute = _minute;
}
unsigned long SCHEDULING::getTime()
{
    return now();
}
String SCHEDULING::getOnTime()
{
    uint8_t h = ontime.hour;
    uint8_t m = ontime.minute;
    return (h < 10 ? "0" : "") + String(h) + ":" + (m < 10 ? "0" : "") + String(m) + ":00";
}
String SCHEDULING::getOffTime()
{
    uint8_t h = offtime.hour;
    uint8_t m = offtime.minute;
    return (h < 10 ? "0" : "") + String(h) + ":" + (m < 10 ? "0" : "") + String(m) + ":00";
}
void SCHEDULING::run()
{
    if (timeStatus() != timeNotSet)
    {
        time_t t = now();
        int h = hour(t);
        int m = minute(t);
        if (h == ontime.hour && m == ontime.minute && !triggered) // Run Once
        {
            // Turn on ALL lights
            for (uint8_t i = 0; i < LED_COUNT; i++)
            {
                led->on(i);
            }
            triggered = true;
        }
        else if (h == offtime.hour && m == offtime.minute && triggered) // Run Once
        {
            // Turn off ALL lights
            for (uint8_t i = 0; i < LED_COUNT; i++)
            {
                led->off(i);
            }
            triggered = false;
        }
    }
}