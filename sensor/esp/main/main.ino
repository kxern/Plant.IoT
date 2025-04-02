#include <WiFi.h>
#include "config.h"
#include <PubSubClient.h>
// #include <ArduinoJson.h>

constexpr int sensorPin = 34;   // Set input Pin

unsigned long lastSensorReadTime = 0;
const unsigned long sensorReadInterval = 60 * 60 * 1000; // 1h (in ms) interval for reading sensor

WiFiClient espClient; // Create a WiFi client object for establishing a WiFi connection
PubSubClient client(espClient); // Create an MQTT client object using the WiFi client to communicate over the network

void setup() {
  Serial.begin(115200); // Initialize serial communication at a baud rate of 115200

  analogReadResolution(12); // Set resolution of the analog-to-digital converter to 12 bits
  analogSetAttenuation(ADC_11db); // Set the analog input attenuation to 11dB for a wider input range
  
  connectWifi();
  
  client.setServer(mqttServer, mqttPort);
  connectMQTT();
}

void loop() { 
  unsigned long currentMillis = millis(); // Get current time in ms

  // Check if it's time to read the sensor based on the defined interval
  if (currentMillis - lastSensorReadTime >= sensorReadInterval){
    lastSensorReadTime = currentMillis; // update last read time to current time 
    int rawValue = readSensorRaw();
    int moisture = moisturePercent(rawValue);
    //
    // Send MQTT Json
  }

  client.loop();
  delay(5000); // 5 Sec delay
}


int readSensorRaw(){
  int rawValue = analogRead(sensorPin);
  Serial.println("Raw Value: " + String(rawValue));
  return rawValue;
}

int moisturePercent(int val){
  // Map the raw sensor value (val) from the range of dryValue to wetValue
  // to a percentage value between 0 and 100.
  int moisturePercent = map(val, dryValue, wetValue, 0, 100);

  // Constrain the moisture percentage to be within the range of 0 to 100 to avoid invalid or out-of-range values.
  moisturePercent = constrain(moisturePercent, 0, 100);
  
  Serial.println("Moisture in percent:" + String(moisturePercent) + "%");
  return moisturePercent;
  }

void connectWifi(){
  Serial.println("Connecting to WiFi " + String(ssid));
  WiFi.begin(ssid, pass);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP: " + WiFi.localIP().toString()); // Print IP
}

void connectMQTT(){
  int attempts = 0;
  int maxAttempts = 60; // Maximum number of attempts (5 min total) 
  while (!client.connected() && attempts < maxAttempts){
    Serial.println("Connecting to MQTT..");
  if (client.connect(clientName, mqttUser, mqttPass)){
    Serial.println("MQTT connected");
  } else {
    // If connection fails, print the error and retry
    Serial.println("failed with state " + String(client.state()));
    attempts++;
    delay(5000); // 5 Sec delay
    }
  }
  if (attempts >= maxAttempts){ // Shutdown after maxAttempts
    Serial.println("Max number of connection attempts reached.");
    Serial.println("Please press the reset button to restart.");
    Serial.println("Entering shutdown mode...");
    esp_deep_sleep_start();
  }
}


