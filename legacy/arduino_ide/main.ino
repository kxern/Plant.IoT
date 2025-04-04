#include <WiFi.h>
#include "config.h"
#include <PubSubClient.h>
#include "mSensor.h"
// #include <ArduinoJson.h>

unsigned long lastSensorReadTime = 0;                // Tracks the last time the sensor was read
const unsigned long sensorReadInterval = 10 * 1000;  // Interval for reading sensor 10 Sec (in ms)

WiFiClient espClient;            // WiFi client object used for network communication
PubSubClient client(espClient);  // MQTT client object that uses WiFi client to communicate over MQTT

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