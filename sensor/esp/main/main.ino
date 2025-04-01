#include <WiFi.h>
#include "config.h"

constexpr int sensorPin = 34;
constexpr int wetValue = 3300;
constexpr int dryValue = 2500;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
  connWifi();
}

void loop() { 
  int rawValue = readSensorRaw();
  int moisture = moisturePercent(rawValue);
  delay(1000);
}

int readSensorRaw(){
  int rawValue = analogRead(sensorPin);
  Serial.println("Raw Value: " + String(rawValue));
  return rawValue;
}

int moisturePercent(int val){
  int moisturePercent = map(val, dryValue, wetValue, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);
  Serial.println("Moisture in percent:" + String(moisturePercent) + "%");
  return moisturePercent;
}

void connWifi(){
  Serial.println("Connecting to WiFi " + String(ssid));
  WiFi.begin(ssid, pass);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print IP
  Serial.println("WiFi connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}


