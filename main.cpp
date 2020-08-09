/*
 * main.cpp
 * chris hamby 
 * last edit: 6-Aug-2020
 * 
 * use a teensy 3.2 to control an addressable LED Strip
*/


//#include "patterns.h"
 //#include "strip_spi.h"
 #include <Arduino.h>
 #include "config.h"
 #include "led_strip.h"
 #include "led_midi.h"
 #include "led_controller.h"
 #include "hardware.h"

/* defined as external in hardware.h */
LED_STRIP MY_STRIP = LED_STRIP(NUM_LEDS);
LED_Controller MY_CONTROLLER = LED_Controller(&MY_STRIP);

void setup() {
  Serial.begin(9600);   // enable this if needed
  initMidi();           // initialize the midi listener
  init_hardware();      // initialize the hardware (i.e. potentiometer pins)
}


/* the operating system only runs the controller function from controller.cpp */
 void loop() {
   MY_CONTROLLER.LED_STRIP_RUNNER(); 
 }
 