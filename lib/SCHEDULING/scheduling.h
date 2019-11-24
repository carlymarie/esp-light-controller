#ifndef _SCHEDULING_H_
#define _SCHEDULING_H_
#include <Arduino.h>
#include <TimeLib.h>
#include "light.h"
/**
 * TODO: Implement this class with a RTC
 */
struct schedule_t
{
    uint8_t hour;
    uint8_t minute;
};

class SCHEDULING
{
public:
    void setEpoch(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint16_t);
    void setOnTime(uint8_t, uint8_t);
    void setOffTime(uint8_t, uint8_t);
    String getOnTime();
    String getOffTime();
    unsigned long getTime();
    void run();

private:
    schedule_t ontime;
    schedule_t offtime;
    bool triggered;
};
extern SCHEDULING *schedule;
#endif // _SCHEDULING_H