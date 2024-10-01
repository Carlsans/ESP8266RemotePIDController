#include "Sensor.h"
extern float Setpoint, Input, Output;
Sensor::Sensor(){
    oneWire = OneWire(TEMP_SENSOR_PIN);
    sensors = DallasTemperature(&oneWire);
}

int32_t Sensor::readSensor(){
  int32_t starttime = millis();
  float sensortemp;
  sensors.requestTemperatures();
  sensortemp = sensors.getTempC(tempsens);
  if(sensortemp > 0){
    Input = sensortemp;
  }
  return millis() - starttime;
}
void Sensor::setup_sensors(){
  sensors.begin();
  //Serial.println(sensors.getDeviceCount(), DEC);
  if (!sensors.getAddress(tempsens, 0)) Serial.println("Unable to find address for Device 0");
  sensors.setResolution(tempsens, 12); // was 9
  readSensor();
  Serial.println(Input);
  
}