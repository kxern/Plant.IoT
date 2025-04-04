#ifndef CONFIG_H
#define CONFIG_H

// Sensor configuration
constexpr int dryValue = 2670;
constexpr int wetValue = 1360;

// WiFi Credentials (extern declarations)
extern const char* ssid;
extern const char* pass;

// MQTT Credentials (extern declarations)
extern const char* mqttServer;
extern const int mqttPort;
extern const char* mqttUser;
extern const char* mqttPass;

// MQTT Topic (extern declaration)
extern const char* mqttTopic;

#endif