#include <Arduino.h>
#include "http.h"
#include "ap.h"
#include "scheduling.h"
HTTP http;
AP ap;
SCHEDULING *schedule = new SCHEDULING();
LIGHT *led = new LIGHT();
void setup()
{
    Serial.begin(9600);
    ap.setup();
    http.setup();
}
void loop()
{
    schedule->run();
}