#include "mSensor.h"
#include <Arduino.h>

SoilMoistureSensor::SoilMoistureSensor(int pin, int dryValue, int wetValue) {
  this->pin = pin;
  this->dryValue = dryValue;
  this->wetValue = wetValue;
}

void SoilMoistureSensor::begin() {
  pinMode(pin, INPUT);  // Set input Pin
}

int SoilMoistureSensor::readRaw() {
  return analogRead(pin);  // Read raw sensor value
}

int SoilMoistureSensor::getMoisture() {
  int rawValue = readRaw();  // Read raw value

  // Map the raw sensor value (val) from the range of dryValue to wetValue
  // to a percentage value between 0 and 100.
  int moisturePercent = map(rawValue, dryValue, wetValue, 0, 100);

  // Constrain the moisture percentage to be within the range of 0 to 100 to avoid invalid or out-of-range values.
  moisturePercent = constrain(moisturePercent, 0, 100);
  Serial.println("Raw value: " + String(rawValue));
  Serial.println("Moisture in percent: " + String(moisturePercent) + "%");
  return moisturePercent;
}