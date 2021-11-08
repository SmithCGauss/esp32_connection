#include "WiFi.h"
#include <Wire.h>
#include "ESPAsyncWebServer.h"

// Set your access point network credentials
const char *ssid = "cyb";
const char *password = "3dxiehuinb";

//datas pin
#define RX 18
#define TX 19

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);


String readpin()
{
    // int cyb1 = analogRead(pin1), cyb2 = analogRead(pin2);
    // if (cyb1 >= 600 && cyb2 >= 600)
    // {
    //     return "start";
    // }
}

//发送消息
void send_txt()
{
    server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(200, "text/plain", readpin().c_str()); });
    delay(20);
}



void setup()
{
    // Serial port for debugging purposes
    Serial.begin(115200);
    WiFi.softAP(ssid, password);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    // Start server
    server.begin();

    

}

void loop()
{





    
}
