#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>  // Muss hier sein!

extern const char* ssid;
extern const char* pass;
void connectWifi();

#endif