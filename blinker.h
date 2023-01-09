/**************************************************************
 * 
 * https://forum.arduino.cc/t/solved-passing-a-function-as-argument-for-a-2nd-function/81749/8
 * https://forum.arduino.cc/t/pointers-to-function/58518/3
 * 
 * https://forum.arduino.cc/t/esp32-xtaskcreatepinnedtocore-usage-in-a-class/630469
 * 
 **************************************************************/
#ifndef blinker_h
#define blinker_h

#define BLINKER_LIBRARY_VERSION 20230108   //only used for information sharing

#include <Arduino.h>

#define INCLUDE_vTaskDelay  1   // make sure the compiler includes the vTaskDelay 

// define the template for a function to increase readability of the callback
typedef void (*blinkCallbackTemplate) (bool);
void blinkCallbackDefault(bool);  //an empty function to use as a safe placeholder.


class blinker
{
  public:
    blinker(int pin);
    void begin();
//    void suspend();   //TBD https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.html#_CPPv412vTaskSuspend12TaskHandle_t
    int dwell=500;     // how long to wait (ms) before toggling state
    void setCallback(blinkCallbackTemplate);
  private:
    int _pin;           // which pin is the LED on
    bool _isOn = false; // is the LED currently ON
    const int _taskCore = 1;
    const int _taskPriority = 1;
    TaskHandle_t _blinkerTask;
    blinkCallbackTemplate _pCallbackFunction = blinkCallbackDefault;  //pointer to function that executes after the LED toggles//    static void _engineTask(void *);   //where all the execution happens

  private: static void _engineTask(void *pvParameters);   //where all the execution happens

};

#endif   //blinker_h
