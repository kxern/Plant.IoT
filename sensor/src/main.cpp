#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"
#include "mSensor.h"
#include "wifi_utils.h"
#include "mqtt.h"
// #include <ArduinoJson.h>

unsigned long lastSensorReadTime = 0;                // Tracks the last time the sensor was read
const unsigned long sensorReadInterval = 10 * 1000;  // Interval for reading sensor 10 Sec (in ms)

SoilMoistureSensor sensor1(34, dryValue, wetValue);  // Create an instance of SoilMoistureSensor

void setup() {
  Serial.begin(115200);            // Start serial communication at 115200 baud rate
  analogReadResolution(12);        // Set resolution of the analog-to-digital converter to 12 bits
  analogSetAttenuation(ADC_11db);  // Set the analog input attenuation to 11dB for a wider input range
  sensor1.begin();                 // Initialize sensor1
  connectWifi();                   // Attempt to connect to MQTT server

  client.setServer(mqttServer, mqttPort);
  client.setSocketTimeout(5);  // 5 Sec Timeout
  connectMQTT();
}

void loop() {
  unsigned long currentMillis = millis();  // Get current time in ms

  // Check if it's time to read the sensor based on the defined interval
  if (currentMillis - lastSensorReadTime >= sensorReadInterval) {
    lastSensorReadTime = currentMillis;     // Update the last sensor1 read time to current time
    int rawVal1 = sensor1.readRaw();        // Read the raw sensor value
    int moisture1 = sensor1.getMoisture();  // Get the moisture level (processed value)

    // TODO: Send MQTT message in JSON format
  }

  client.loop();  // Maintain MQTT connection and process incoming/outgoing messages
  delay(1000);    // 1 Sec delay
}