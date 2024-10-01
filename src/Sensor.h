#pragma once
#ifndef Sensor_h
#define Sensor_h
#include <DallasTemperature.h>
#include "pins.h"
extern float Setpoint, Input, Output;
class Sensor
{
private:
    OneWire oneWire;
    DallasTemperature sensors;
    DeviceAddress tempsens;
public:
    Sensor();
    int32_t readSensor();
    void setup_sensors();  
};


#endif // Sensor_h