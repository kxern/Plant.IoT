#include "config.h"

// WiFi Credentials (definitions)
const char* ssid = "YOUR_WIFI_SSID";         // Replace with your network name
const char* pass = "YOUR_WIFI_PASSWORD";     // Replace with your network password

// MQTT Credentials (definitions)
const char* mqttServer = "BROKER_IP";        // MQTT broker address
const int mqttPort = 1883;                    // Default MQTT port
const char* mqttUser = "BROKER_USERNAME";     // Broker authentication
const char* mqttPass = "BROKER_PASSWORD";     // Broker authentication

// MQTT Topic (definition)
const char* mqttTopic = "sensors/soil/esp1";  // Customize your topic hierarchy