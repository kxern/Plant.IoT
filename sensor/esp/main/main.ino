#include <WiFi.h>
#include "config.h"
#include <PubSubClient.h>
#include "mSensor.h"
// #include <ArduinoJson.h>

unsigned long lastSensorReadTime = 0;
const unsigned long sensorReadInterval = 10 * 1000;  // 10 Sec (in ms) interval for reading sensor

WiFiClient espClient;            // Create a WiFi client object for establishing a WiFi connection
PubSubClient client(espClient);  // Create an MQTT client object using the WiFi client to communicate over the network

SoilMoistureSensor sensor1(34, dryValue, wetValue);  // Create an instance of SoilMoistureSensor

void setup() {
  Serial.begin(115200);            // Initialize serial communication at a baud rate of 115200
  analogReadResolution(12);        // Set resolution of the analog-to-digital converter to 12 bits
  analogSetAttenuation(ADC_11db);  // Set the analog input attenuation to 11dB for a wider input range
  sensor1.begin();                 // Initialize sensor1
  connectWifi();

  client.setServer(mqttServer, mqttPort);
  client.setSocketTimeout(5);  // 5 Sec Timeout
  connectMQTT();
}

void loop() {
  unsigned long currentMillis = millis();  // Get current time in ms

  // Check if it's time to read the sensor based on the defined interval
  if (currentMillis - lastSensorReadTime >= sensorReadInterval) {
    lastSensorReadTime = currentMillis;  // update last read time to current time
    int rawVal1 = sensor1.readRaw();
    int moisture1 = sensor1.getMoisture();
    //
    // Send MQTT Json
  }

  client.loop();
  delay(1000);  // 1 Sec delay
}





void connectWifi() {
  Serial.println("Connecting to WiFi " + String(ssid));
  WiFi.begin(ssid, pass);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP: " + WiFi.localIP().toString());  // Print IP
}

void connectMQTT() {
  int attempts = 0;
  const int maxAttempts = 60;                                             // 5 Minute (60x5s)
  String clientId = "ESP32-" + String((uint32_t)ESP.getEfuseMac(), HEX);  // Dynamic ClientID

  while (!client.connected() && attempts < maxAttempts) {
    Serial.println("Attempt " + String(attempts + 1) + " of " + String(maxAttempts));

    if (client.connect(clientId.c_str(), mqttUser, mqttPass)) {
      Serial.println("MQTT connected!");
      Serial.println("Client ID: " + clientId);
      return;
    } else {
      Serial.println("Failed, state: " + String(client.state()));
      Serial.println("Error: " + getMQTTError(client.state()));
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
  esp_deep_sleep_start();
}

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