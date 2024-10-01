#include "PwmTimer.h"

PwmTimer* PwmTimer::instance = nullptr;
void PwmTimer::TimerHandler()
{
  static uint32_t interval;
  if(this->toggle){
    interval =(uint32_t) (this->Timerinterval * this->Output/255 )+1;
  }else{
    interval =(uint32_t) (this->Timerinterval * (1 - this->Output/255))+1;
    // Read sensor here and remove sensor reading time from the interval
    /*uint32_t sensorreadingtime = Tempsensor.readSensor();
    if(interval > sensorreadingtime){
      interval -= sensorreadingtime;
    }
    else{
      interval = 0 ;
    }*/
    
  }
  PwmTimer::instance = this;
  
  this->ITimer.setInterval( interval * 1000 , PwmTimer::TimerHandlerStatic);

  digitalWrite(this->Ssrpin, this->toggle);
  if(this->toggle){
    lastturnontime = turnontime;
    turnontime = millis();
  }else{
    lastturnofftime = turnofftime;
    turnofftime = millis();
  }

  if(!this->toggle)
    hasbeenturnedoffbeforesensorbeingread = true;
  this->toggle = !this->toggle;
}
String PwmTimer::safetycheck(){
  return "Turn on time=" + String(turnontime) + " Turn off time="+ String(turnofftime)+" time between turn on="+String(turnontime-lastturnontime)+" time between turn off="+String(turnofftime-lastturnofftime);
}
void PwmTimer::TimerHandlerStatic()
{
    if (PwmTimer::instance) {
        PwmTimer::instance->TimerHandler();
    }
}
bool PwmTimer::canIupdateSensor(){
  if(hasbeenturnedoffbeforesensorbeingread){
    hasbeenturnedoffbeforesensorbeingread = false;
    return true;
  }
  return false;
}
void PwmTimer::startTimer(){
    // Timer
  // Interval in microsecs
 PwmTimer::instance = this;
 if (ITimer.attachInterruptInterval(this->Timerinterval * 1000, PwmTimer::TimerHandlerStatic))
  {
    Serial.print(F("Starting  ITimer OK, millis() = "));
    Serial.println(millis());
    //sendmessage("Starting  ITimer"+String(millis()));
  }
  else{
    Serial.println(F("Can't set ITimer. Select another freq. or timer"));
    //sendmessage("Can't set ITimer. Select another freq. or timer");
    }
}
void PwmTimer::disableTimer(){
    this->ITimer.disableTimer();
}



PwmTimer::~PwmTimer()
{
}
