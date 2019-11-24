#ifndef _HTTP_H_
#define _HTTP_H_
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h> // Include the SPIFFS library
#else
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h> // Include the SPIFFS library
#endif
#include <ArduinoJson.h>
#include "configuration.h"
#include "light.h"
#include "scheduling.h"
class HTTP
{
public:
    void setup();

private:
    AsyncWebServer *server;
};
#endif // _HTTP_H_