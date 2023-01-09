/**************************************************************
 * goal: run a thread/task as a library
 * plan: a simple library that blinks led, but as task (no setup, no loop
 * 
 * https://www.circuitbasics.com/programming-with-classes-and-objects-on-the-arduino/
 * https://docs.arduino.cc/learn/contributions/arduino-creating-library-guide
 * https://roboticsbackend.com/arduino-object-oriented-programming-oop/
 * 
 * This emulates a library called "blinker"
 * only 3 lines are needed:
 *   -include
 *   -declare instance
 *   -begin (in setup)
 *  
 * with default settings, toggles the RX LED every half second, and sends a messge to Serial
 * 
 **************************************************************/
#include "blinker.h"

#define RX_LED   5    //LED3: Serial port indicator, RXD2(IO5) When there is data flow, the indicator light is on;

blinker ledServer(RX_LED);  //declare an instance of the class

//-------------------------------------------------------------------
void blinkCallbackUpgrade(bool bStatus) {
  //Demonstrating the ability to override the default callback fuction.
  Serial.print(F("LED is ON?: ")); Serial.println(bStatus);
}

//-------------------------------------------------------------------
void serialStart() {
  // this is a convenience function so the setup look cleaner
  Serial.begin(115200);
    
  long serialInterval = 10000;   // interval to wait
  unsigned long previous = millis();   // hold current 'time'
  while (!Serial) {
    // wait for serial port to connect. Needed for built-in USB port only
    if (millis() - previous >= serialInterval) {
      // exceeded the allowed wait-time; give up and don't use the serial communications
      break;
    } else {
      delay(50);
    }
  }
  delay(250);  //it seems that occassionally serial is ready a few moments before it can be written to
  Serial.println();

  Serial.print( F("Compiled: "));  //https://forum.arduino.cc/t/displaying-date-time-and-ide-compiler-version-in-serial-monitor/154290/3
  Serial.print( F(__DATE__));
  Serial.print( F(", "));
  Serial.print( F(__TIME__));
  Serial.print( F(", "));
  Serial.println( F(__VERSION__));
  Serial.print( F("From: "));
  Serial.println( F(__FILE__));

  Serial.println(F("Initializing ... "));
}

//###################################################################
void setup() {
  serialStart();
  
//  ledServer.setCallback(*blinkCallbackUpgrade);
//  ledServer.dwell = 250;
  ledServer.begin();

}

//-------------------------------------------------------------------
void loop() {
//  Serial.println(F("Loops are great."));
  vTaskDelay( 100 );
}
