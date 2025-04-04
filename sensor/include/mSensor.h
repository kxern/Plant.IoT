#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>


// SoilMoistureSensor class definition
// This class is used to interface with a soil moisture sensor,
// providing methods to read raw sensor data and calculate moisture percentage.


class SoilMoistureSensor {
public:

  // Constructor: Initializes the sensor with pin and moisture thresholds (dry and wet values)
  SoilMoistureSensor(int pin, int dryValue, int wetValue);
  void begin();       // begin(): Initializes the sensor by setting the appropriate pin mode
  int readRaw();      // readRaw(): Reads and returns the raw sensor value (analog input)
  int getMoisture();  // getMoisture(): Maps the raw sensor value to a moisture percentage (0-100%)

private:

  int pin;       // Pin number where the sensor is connected
  int dryValue;  // Raw value corresponding to dry soil
  int wetValue;  // Raw value corresponding to wet soil
};

#endif