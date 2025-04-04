#ifndef MQTT_H
#define MQTT_H

#include <WiFi.h>
#include <PubSubClient.h>

extern PubSubClient client;
void connectMQTT();
String getMQTTError(int state);

#endif