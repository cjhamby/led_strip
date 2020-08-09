/* 
 * leds.cpp
 * chris hamby
 * last edit: 6 Aug 2020 
 * 
 * functions to change data held in LED nodes
*/

#include <Arduino.h>
#include "led_strip.h"
#include "led_controller.h"
#include "config.h"
//#include "led_midi.h"
//#include "colors.h"
#include "patterns.h"


/* turn an individual LED on */
/* index is relative to the strip beginning */
void  LED_Controller::setLEDOn(int index){
    if(index<0 || index>num_leds) return;
    setLEDBrightness(index, DEFAULT_BRIGHTNESS);
}

/* give an individual LED a brightness of 0 */
void  LED_Controller::setLEDOff( int index){
    if(index<0 || index>num_leds) return;
    setLEDBrightness(index, OFF);
}



/*
 * give an individual LED a color value
 * index is relative to the strip beginning
*/
void  LED_Controller::setLEDColor_Bytes( int index, unsigned char newR, unsigned char newG, unsigned char newB ) {
    LED_PTR thisLED = myStripPtr->get_data_at_index(index); 
    thisLED->R_VALUE = newR;
    thisLED->G_VALUE = newG;
    thisLED->B_VALUE = newB;
}

/*
 * give an individual LED a brightness value
 * index is relative to the strip beginning
*/
void  LED_Controller::setLEDBrightness(int index, unsigned char newBrightness){
    LED_PTR thisLED = myStripPtr->get_data_at_index(index);
    thisLED->BRIGHTNESS = newBrightness;
}


/* lower an individual LED's brightness level */
int  LED_Controller::dimLED(int index){
    LED_PTR thisLED = myStripPtr->get_data_at_index(index);

    if(thisLED->BRIGHTNESS <= FADE_OUT_AMT){
        setLEDOff(index);
        return 0;
    }
    thisLED->BRIGHTNESS -= FADE_OUT_AMT;
    return 1;
}


/* give an individual LED a color value */
void  LED_Controller::setLEDColor(int index, long hexColorValue) {
    unsigned char parseR = (unsigned char)(hexColorValue>>16);
    unsigned char parseG = (unsigned char)(hexColorValue>>8);
    unsigned char parseB = (unsigned char)(hexColorValue);
    setLEDColor_Bytes(index, parseR, parseG, parseB);
}


/* index is relative to the shifted beginning */
void  LED_Controller::setLEDOn_TrueIndex(int index){
    int trueIndex = index - myStripPtr->shift_offset;
    if(trueIndex<0) trueIndex+=num_leds;
    setLEDBrightness(trueIndex, DEFAULT_BRIGHTNESS);
}

void  LED_Controller::setLEDOff_TrueIndex(int index){
    int trueIndex = index - myStripPtr->shift_offset;
    if(trueIndex<0)
        trueIndex+=num_leds;
    setLEDBrightness(trueIndex, OFF);
}




/* --------- WHOLE STRIP functions --------- */

//  give the strip a single uniform color
void LED_Controller::setUniformColor(long hexColorValue){
    unsigned char parseR = (unsigned char)(hexColorValue>>16);
    unsigned char parseG = (unsigned char)(hexColorValue>>8);
    unsigned char parseB = (unsigned char)(hexColorValue);
    setUniformColor_Bytes(parseR, parseG, parseB);
}

void LED_Controller::setUniformColor_Bytes(unsigned char newR, unsigned char newG, unsigned char newB){
    for(int i=0; i<myStripPtr->length; i++)
        setLEDColor_Bytes(i, newR, newG, newB);
}



//  give the strip a single uniform brightness
void LED_Controller::setUniformBrightness(unsigned char newBrightness){
    for(int i=0; i<myStripPtr->length; i++)
        setLEDBrightness(i, newBrightness);
}


//  set the strip brightness to 0
void LED_Controller::setAllOff(){
    for(int i=0; i<myStripPtr->length; i++)
         setLEDOff(i);
}