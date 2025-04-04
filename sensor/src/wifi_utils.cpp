#include <WiFi.h>
#include "wifi_utils.h"
#include "config.h"

#include <Arduino.h>


void connectWifi() {
  Serial.println("Connecting to WiFi " + String(ssid));  // Notify about the WiFi connection attempt
  WiFi.begin(ssid, pass);                                // Start WiFi connection using SSID and password
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);         // Wait for 500 milliseconds before checking the connection status again
    Serial.print(".");  // Output a dot for each attempt
  }
  Serial.println("WiFi connected");
  Serial.println("IP: " + WiFi.localIP().toString());  // Print the local IP address once connected
}