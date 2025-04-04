#include <WiFi.h>
#include "mqtt.h"
#include "wifi_utils.h"
#include "config.h"

#include <ETH.h>

WiFiClient espClient;            // WiFi client object used for network communication
PubSubClient client(espClient);  // MQTT client object that uses WiFi client to communicate over MQTT

void connectMQTT() {
  int attempts = 0;                                                       // Initialize connection attempts counter
  const int maxAttempts = 60;                                             // Maximum number of attempts 5 Minute (60x5s)
  String clientId = "ESP32-" + String((uint32_t)ESP.getEfuseMac(), HEX);  // Dynamic ClientID

  // Loop to try connecting to the MQTT server
  while (!client.connected() && attempts < maxAttempts) {
    Serial.println("Attempt " + String(attempts + 1) + " of " + String(maxAttempts));

    if (client.connect(clientId.c_str(), mqttUser, mqttPass)) {  // Attempt to connect with provided credentials
      Serial.println("MQTT connected!");
      Serial.println("Client ID: " + clientId);  // Print the generated client ID for debugging
      return;
    } else {
      Serial.println("Failed, state: " + String(client.state()));  // Print connection state if it fails
      Serial.println("Error: " + getMQTTError(client.state()));    // Print human-readable error message
      attempts++;
      delay(5000);

      // Check WiFi-Connection
      if (WiFi.status() != WL_CONNECTED) {
        connectWifi();
      }
    }
  }

  Serial.println("Max number of connection attempts reached.");
  Serial.println("Please press the reset button to restart.");
  Serial.println("Entering shutdown mode...");
  esp_deep_sleep_start();  // Enter deep sleep mode if the maximum attempts are reached
}

// Function to get a human-readable MQTT error message based on the connection state
String getMQTTError(int state) {
  switch (state) {
    case -4: return "Connection timeout";
    case -3: return "Connection lost";
    case -2: return "Connect failed";
    case -1: return "Disconnected";
    case 1: return "Bad protocol";
    case 2: return "ID rejected";
    case 3: return "Server unavailable";
    case 4: return "Bad credentials";
    case 5: return "Not authorized";
    default: return "Unknown error";
  }
}