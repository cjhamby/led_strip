/* 
 * hardware.h
 * chris hamby
 * 
 * hardware details, such as pins and buttons
 * interrupt functions 
 * idle function
*/

#ifndef HARDWARE_H_
#define HARDWARE_H_
#include "config.h"
#include "led_strip.h"
#include "led_controller.h"


extern LED_STRIP MY_STRIP;
extern LED_Controller MY_CONTROLLER;


#define LEFT_SIDE           0
#define RIGHT_SIDE          1

extern void cyclePattern();
extern void init_hardware();
extern void idle();

#endif