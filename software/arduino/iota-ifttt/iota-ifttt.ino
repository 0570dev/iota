#include <LM75.h>
#include <Wire.h>

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "OneButton.h"

#define WIFI_SSID           "My Wifi"
#define WIFI_PASSWORD       "My Password"

// Only update IFTTT_KEY and IFTTT_EVENT using your own Key and Event-name. URL is generated in singleClick() using these parameters.
#define IFTTT_URL           "http://maker.ifttt.com"
#define IFTTT_KEY           "IFTTT KEY";
#define IFTTT_EVENT         "IFTTT EVENT NAME";

#define BUTTON_PIN          0   // D3
OneButton button(BUTTON_PIN, true);
LM75 temp_sensor;

float getTemperature() {
  temp_sensor.shutdown(false);
  delay(100);
  float temperature = temp_sensor.temp();
  temp_sensor.shutdown(true);
  return temperature;
}

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();

  Wire.begin();

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting wifi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(" connected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  pinMode(BUTTON_PIN, INPUT);
  button.attachClick(singleClick);
}

void loop() {
  button.tick();
}

void singleClick() {
  String url;
  url += IFTTT_URL;
  url += "/trigger/";
  url += IFTTT_EVENT;
  url += "/with/key/";
  url += IFTTT_KEY;
  url += "?value1=";
  url += String(getTemperature());

  HTTPClient http;
  http.begin(url); 
  
  int httpCode = http.GET();
  if(httpCode == 200) {
    Serial.println("IFTTT OK");
  } else {
    Serial.print(httpCode);
    Serial.println("IFTTT FAIL");
  }

  http.end();
}

