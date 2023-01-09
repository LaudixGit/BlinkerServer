/**************************************************************
 * 
 **************************************************************/
#include <Arduino.h>
#include "blinker.h"

// the class constructor
blinker::blinker(int setPin)
{
  this->_pin = setPin;
  pinMode(this->_pin, OUTPUT);
  digitalWrite(this->_pin,!_isOn);   //because the LED is active-low ON = false
}

void blinker::setCallback(blinkCallbackTemplate pCbFunction){
  _pCallbackFunction = pCbFunction;
}

void blinker::_engineTask(void *pvParameters){
  // this is what continuously runs to blink the LED
  Serial.println(F("It's the engine running"));
  blinker *l_pThis = (blinker *) pvParameters;  //create a handle to the instance of the class that spawned this task
  unsigned long ledLastUpdate = 0;  // when was the LED last toggled
  int ledDwell = 500;
  bool isLedOn = false;
  int ledPin = 5;

  while (true){
    if((millis() - ledLastUpdate) > l_pThis->dwell){ // time to check if update is needed
      ledLastUpdate = millis();
      l_pThis->_isOn = !l_pThis->_isOn;  //invert to toggle
      l_pThis->_pCallbackFunction(l_pThis->_isOn);
      digitalWrite(l_pThis->_pin,!l_pThis->_isOn);   //because the LED is active-low ON = false
    }
    vTaskDelay( 100 );
  }
  delay(50); //Wait a little before killing task
  vTaskDelete( NULL );  // this never gets exectuted, but if it DOES, the task will close gracefully
}

void blinker::begin(){
  Serial.print(F("\nBlinker Library version: ")); Serial.println(BLINKER_LIBRARY_VERSION);
  xTaskCreatePinnedToCore(
      this->_engineTask,      //Function to implement the task 
      "BlinkerEngine",        //Name of the task
      768,                    //Stack size in words (tested: requires minimmum of 768)
      this,                   //Task input parameter 
      _taskPriority,          //Priority of the task 
      &_blinkerTask,          //Task handle.
      _taskCore);             //Core where the task should run 
}


void blinkCallbackDefault(bool) {
  //an empty function to use as a safe placeholder.
  Serial.println(F("Hey! the callback worked!!"));
}
