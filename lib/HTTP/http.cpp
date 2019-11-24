#include "http.h"
void HTTP::setup()
{
    led->setup();
    server = new AsyncWebServer(HTTP_PORT);
    if (!SPIFFS.begin())
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }
    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html", String(), false);
    });

    // Provides CSS to the web UI
    server->on("/css/site.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/css/site.css", String(), false);
    });

    // Provides JS to the web UI
    server->on("/js/init.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/js/init.js", String(), false);
    });

    // Provides information to the web UI
    server->on("/info.json", HTTP_GET, [](AsyncWebServerRequest *request) {
        StaticJsonDocument<200> doc;

        // create an object
        JsonObject object = doc.to<JsonObject>();
        object["datetime"] = schedule->getTime();
        object["ontime"] = schedule->getOnTime();
        object["offtime"] = schedule->getOffTime();
        String data;
        serializeJson(doc, data);
        request->send(200, "application/json", data);
    });
    server->on("/relays.json", HTTP_GET, [this](AsyncWebServerRequest *request) {
        StaticJsonDocument<1024> doc;
        // JSON Payload: {"gpio": 1, "state": 1, "gpio": 2, "state": 0}

        // create an array
        JsonArray array = doc.to<JsonArray>();
        for (uint8_t i = 0; i < LED_COUNT; i++)
        {
            JsonObject relay = array.createNestedObject();
            relay["gpio"] = i;
            relay["state"] = led->state(i);
        }

        String data;
        serializeJson(doc, data);
        request->send(200, "application/json", data);
    });
    // Sets specific pins to high or low
    server->on("/relay", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [this](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
        // JSON Payload: {"gpio": 1, "state": 1}
        StaticJsonDocument<200> doc;
        deserializeJson(doc, (const char*)data);
        if(doc["state"].as<bool>()){ // 
            // Turn on LED at specified GPIO
            led->on(doc["gpio"].as<uint8_t>());
        }else{
            // Turn off LED at specified GPIO
            led->off(doc["gpio"].as<uint8_t>());
        }
        
        request->send(200, "application/json", "{\"status\": 200}"); });

    // Sets current time/date
    server->on("/datetime", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
        StaticJsonDocument<512> doc;
        deserializeJson(doc, data);
        schedule->setEpoch(doc["hour"], doc["minute"], doc["second"], doc["day"], doc["month"], doc["year"]);
        request->send(200, "application/json", "{\"status\": 200}"); });

    // Sets schedule
    server->on("/schedule", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
        StaticJsonDocument<200> doc;
        deserializeJson(doc, data);
        serializeJson(doc, Serial);
        
        schedule->setOnTime(doc["ontime"].as<JsonObject>()["hour"].as<uint8_t>(),doc["ontime"].as<JsonObject>()["minute"].as<uint8_t>());
        schedule->setOffTime(doc["offtime"].as<JsonObject>()["hour"].as<uint8_t>(),doc["offtime"].as<JsonObject>()["minute"].as<uint8_t>());

        request->send(200, "application/json", "{\"status\": 200}"); });
    server->begin();
}