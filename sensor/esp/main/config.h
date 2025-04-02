#include <PubSubClient.h>

#ifndef CONFIG_H
#define CONFIG_H

// Device settings
const char* clientName = "YOUR_DEVICE_NAME";  // Set your device name here

// Sensor configuration
constexpr int wetValue = 3300;  // Adjust the wet value here
constexpr int dryValue = 2500;  // Adjust the dry value here

// WiFi Credentials
const char* ssid = "YOUR_WIFI_SSID";  // Set your Wi-Fi SSID here
const char* pass = "YOUR_WIFI_PASSWORD";  // Set your Wi-Fi password here

// MQTT Credentials
const char* mqttServer = "YOUR_MQTT_BROKER_IP";  // Set your MQTT broker IP address here
const int mqttPort = 1883;  // Set the MQTT broker port here (default is 1883)
const char* mqttUser = "YOUR_MQTT_USERNAME";  // Set your MQTT username here
const char* mqttPass = "YOUR_MQTT_PASSWORD";  // Set your MQTT password here

// MQTT Topic
const char* mqttTopic = "YOUR_MQTT_TOPIC";  // Set your MQTT topic here

#endif