#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#define pin1 18
#define pin2 19

const char *ssid = "cyb";
const char *password = "3dxiehuinb";

//Your IP address or domain name with URL path
const char *serverdata = "http://192.168.4.1/data";

String data;

unsigned long previousMillis = 0;
const long interval = 5000;
String httpGETRequest(const char *serverName);
void setup()
{
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
}

void loop()
{
    unsigned long currentMillis = millis();
    // Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED)
    {
        data = httpGETRequest(serverdata);
        if (data == "start")
        {
            digitalWrite(pin1, HIGH);
            digitalWrite(pin2, HIGH);
            delay(1500);
            digitalWrite(pin2, LOW);
            digitalWrite(pin1, LOW);
        }

        // save the last HTTP GET Request
        previousMillis = currentMillis;
    }
    else
    {
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
        }
    }
}

String httpGETRequest(const char *serverName)
{
    HTTPClient http;

    // Your IP address with path or Domain name with URL path
    http.begin(serverName);

    // Send HTTP POST request
    int httpResponseCode = http.GET();

    String payload = "--";

    if (httpResponseCode > 0)
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();

    return payload;
}