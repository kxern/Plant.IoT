// sensor.h
#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class SoilMoistureSensor {
public:
    SoilMoistureSensor(int pin, int dryValue, int wetValue);  // Constructor
    void begin();  // Initialize sensor
    int readRaw();  // Read raw sensor value
    int getMoisture();  // Calculate moisture

private:
    int pin;
    int dryValue;
    int wetValue;
};

#endif