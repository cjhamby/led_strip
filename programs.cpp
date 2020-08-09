/* 
 * programs.cpp
 * chris hamby
 * last edit: 6 Aug 2020 
 * 
 * programs are what operate the strip in real-time 
 * used for animations or idling until the color changes
*/

#include <Arduino.h>
#include "hardware.h"
#include "led_controller.h"
#include "patterns.h"
#include "led_strip.h"
#include "config.h"


void LED_Controller::init_program(unsigned char p, long c, unsigned char b){
    if(program_initialized)   return;
    program_initialized = 1;
    
    if(p != NO_PATTERN)       
        init_strip_pattern(p);
    else{
        setUniformColor(c);
        setUniformBrightness(DEFAULT_BRIGHTNESS);
        showLEDStrip();
    }
}

/* Press a button to switch programs */
void LED_Controller::cycle_strip_program(){
    program_initialized = 0;  
    if(++CurrentProgram>=NUM_PROGRAMS)
        CurrentProgram=0;   
}

/* choose a program */
void LED_Controller::change_current_program(unsigned char newProg){
    program_initialized = 0;
    CurrentProgram = newProg;
}


/* set the color to a single color */
void LED_Controller::run_single_color(long c){
    init_program(NO_PATTERN, c, DEFAULT_BRIGHTNESS);
    idle();
}


/* Fade through the colors in the palette */
void LED_Controller::run_color_fader(){
    init_program(NO_PATTERN, MY_PALETTE[0], DEFAULT_BRIGHTNESS);

    // increment MY_COLOR_INDEX to the next value 
    long old_color_index = myColor_index;
    cycle_color();
    fade_into_color(MY_PALETTE[old_color_index], MY_PALETTE[myColor_index]);
}


/*
 * The strip flashes white-blue "ice sparkles"
 * The sparkles alternate LEDs 
*/
void LED_Controller::run_ice_sparkle(){
    init_program(ICESPARKLE_PATTERN, 0, 0);

    for(int i=6; i<=DEFAULT_BRIGHTNESS; i++){
        setUniformBrightness(i);
        showLEDStrip();
        delay(ICESPARKLE_DELAY1);
    }
    for(int i=0; i<=DEFAULT_BRIGHTNESS-6; i++){
        setUniformBrightness(DEFAULT_BRIGHTNESS-i);
        showLEDStrip();
        delay(ICESPARKLE_DELAY1);
    }
    delay(ICESPARKLE_DELAY2);
}




/*   
  if you want to hook up potentiometers, this is the function for you
  check out "patterns.h" for pin definitions  
*/
void LED_Controller::run_pot_control(){
    init_program(NO_PATTERN, DEFAULT_COLOR, DEFAULT_BRIGHTNESS);

    int brPot = (int)( BRPOT_SCALE * analogRead(BRPOT) );
    int rPot = analogRead(RPOT);
    int gPot = analogRead(GPOT);
    int bPot = analogRead(BPOT);

    /* cap the values */
    if (brPot >  31) brPot = 31;
    if (rPot  > 255) rPot = 255;
    if (gPot  > 255) gPot = 255;
    if (bPot  > 255) bPot = 255;

    setUniformColor_Bytes((unsigned char)rPot,(unsigned char)gPot,(unsigned char)bPot);
    setUniformBrightness( (unsigned char)brPot );
    showLEDStrip();
}
 



/* shift the strip in either direction */
void LED_Controller::run_left_shift(){
    init_program(PATTERN1, 0, 0);
    myStripPtr->shift_strip_left();
    showLEDStrip();
    delay(SHIFT_DELAY);
}

void LED_Controller::run_right_shift(){
    init_program(PATTERN1, 0, 0);
    myStripPtr->shift_strip_right();
    showLEDStrip();
    delay(SHIFT_DELAY);
}



/* shift the strip and show the mirror strip - mirrors the "left"/"first" half of the strip */
void LED_Controller::run_mirror_left_shift(){
    init_program(PATTERN1, 0, 0);
    myStripPtr->shift_strip_left();
    showMirrorLEDStrip();
    delay(SHIFT_DELAY);
}

void LED_Controller::run_mirror_right_shift(){
    init_program(PATTERN1, 0, 0);
    myStripPtr->shift_strip_right();
    showMirrorLEDStrip();
    delay(SHIFT_DELAY);
}


/*
 * shift the strip to the right
 * show the "left"/"first" half of the strip
 * the "right"/"second" half of the strip changes
 * the goal is to cycle through all the colors
 * without showing any abrupt transition 
*/
void LED_Controller::run_right_shift_palette(){
    init_program(NO_PATTERN, MY_PALETTE[0], DEFAULT_BRIGHTNESS);

    myColor_index = 0;
    int temp_index = 0;
    cycle_color();
    colorGradient_LeftHalf(MY_PALETTE[temp_index], MY_PALETTE[myColor_index]);
    temp_index = myColor_index;
    cycle_color();
    colorGradient_RightHalf(MY_PALETTE[temp_index], MY_PALETTE[myColor_index]);

    // go through the entire palette 
    for(int j = 0; j<(MY_PALETTE_SIZE-1); j++){
        // shift the strip halfway
        for(int i=0; i<((myStripPtr->length)/2); i++){
            myStripPtr->shift_strip_left();
            showMirrorLEDStrip();
            delay(SHIFT_DELAY);
        }
        // create a gradient on the right (unseen) half of the strip 
        colorGradient_RightHalf(MY_PALETTE[myColor_index], MY_PALETTE[myColor_index+1]);
        cycle_color();
    }
}



/* 
 * accepts input on two analog pins
 * uses that input to create a visualizer of audio loudness
*/
void LED_Controller::run_equalizer(){
    init_program(PATTERN1, 0, 0);

    float vol1 = analogRead(PIN_A1);       // returns a value between 0-1023
    float vol2 = analogRead(PIN_A2);       // stereo control
    int num_on_1 = (int)(vol1*60/1024)-1;  // maps the volume to the number of LEDs
    int num_on_2 = (int)(vol2*60/1024)-1;  // do the same for the right side 
    
    // turn LEDs on or off as necessary 
    for(int i=0; i<myStripPtr->length; i++){
        if((myStripPtr->length - i) < num_on_2)
          setLEDBrightness(i, DEFAULT_BRIGHTNESS);
        else if(i < num_on_1)
          setLEDBrightness(i, DEFAULT_BRIGHTNESS);
        else
          setLEDBrightness(i, 0);
    }
    showLEDStrip();
}

