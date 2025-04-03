#include "mSensor.h"
#include <Arduino.h>

// Constructor for the SoilMoistureSensor, taking pin, dryValue, and wetValue as arguments
SoilMoistureSensor::SoilMoistureSensor(int pin, int dryValue, int wetValue) {
  this->pin = pin;            // Sets the pin the sensor is connected to
  this->dryValue = dryValue;  // Sets the threshold for dry soil (sensor value when the soil is dry)
  this->wetValue = wetValue;  // Sets the threshold for wet soil (sensor value when the soil is completely wet)
}

// Initializes the sensor (sets the pin as an input)
void SoilMoistureSensor::begin() {
  pinMode(pin, INPUT);  // Set input Pin
}

// Reads the raw value from the sensor (analog signal)
int SoilMoistureSensor::readRaw() {
  return analogRead(pin);  // Read raw sensor value
}

// Calculates the moisture level based on the dry and wet thresholds
int SoilMoistureSensor::getMoisture() {
  int rawValue = readRaw();  // Read raw value

  // Map the raw sensor value (val) from the range of dryValue to wetValue
  // to a percentage value between 0 and 100.
  int moisturePercent = map(rawValue, dryValue, wetValue, 0, 100);

  // Constrain the moisture percentage to be within the range of 0 to 100 to avoid invalid or out-of-range values.
  moisturePercent = constrain(moisturePercent, 0, 100);
  Serial.println("Raw value: " + String(rawValue));
  Serial.println("Moisture in percent: " + String(moisturePercent) + "%");
  return moisturePercent;  // Returns the calculated moisture percentage
}