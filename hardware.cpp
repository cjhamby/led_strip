/*
 * hardware.cpp 
 * chris hamby
 * define functions for hardware interactions
 * i.e. 
 * button pressing
 * sleep/wake mode 
*/


#include <Arduino.h>
#include <avr/sleep.h>
#include "hardware.h"
#include "led_controller.h"

void idle() {
  set_sleep_mode(SLEEP_MODE_IDLE);
  noInterrupts();
  sleep_enable();
  interrupts();
  sleep_cpu();
  sleep_disable();
}

void cyclePattern(){ 
  MY_CONTROLLER.cycle_strip_program();
}

void init_hardware(){
  for(int i=0; i<NUM_DIGITAL_PINS; i++)
    pinMode(i, OUTPUT);
  
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  // this interrupt changes the current program when a button is pressed 
  attachInterrupt(digitalPinToInterrupt(14), cyclePattern, RISING );
}