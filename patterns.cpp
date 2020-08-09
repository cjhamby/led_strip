/* 
 * patterns.cpp
 * chris hamby
 * last edit: 6 Aug 2020 
 * 
 * functions that change data held in LED nodes
*/

#include <Arduino.h>
#include "colors.h"
#include "config.h"
#include "led_strip.h"
#include "led_midi.h"
#include "led_controller.h"
#include "patterns.h"


//  initialize the strip with a single color and the default brightness
void LED_Controller::init_strip(){
    setUniformBrightness(DEFAULT_BRIGHTNESS);
    setUniformColor(DEFAULT_COLOR);
}

//  initialize the strip with 0 color and 0 brightness
void LED_Controller::init_strip_off(){
    setUniformBrightness(OFF);
    setUniformColor(OFF);
}

/*
 * Define patterns here! 
 * The pattern is a one-time initialization of the strip colors
 * it can be shifted left or right easily
 * the individual colors may also be accessed, but not as easily
*/
void LED_Controller::init_strip_pattern(unsigned char pattern){
    switch(pattern){
        
        case PATTERN1:  // a nice rainbow gradient
            colorGradient_LeftHalf(RED, GREEN);
            colorGradient_RightHalf(GREEN, PURPLE);
            setUniformBrightness(DEFAULT_BRIGHTNESS);
        break;

        case PATTERN2:  // a...something
            colorGradient_LeftHalf(BLUE, YELLOW);
            colorGradient_RightHalf(BLUE, PURPLE);
            setUniformBrightness(DEFAULT_BRIGHTNESS);
        break;
        
        case ALL_WHITE: // used when the strip is powered
            setUniformColor(WHYTE);
            setUniformBrightness(DEFAULT_BRIGHTNESS);
        break;
        
        case ALL_OFF:   // there's also a function for this
            setUniformColor(OFF);
            setUniformBrightness(OFF);
        break;
        
        case ICESPARKLE_PATTERN: // spaced out leds 
            setUniformBrightness(DEFAULT_BRIGHTNESS);
            for(int i=0; i<num_leds; i++)
                if(i%ICESPARKLE_SPACING==0)    setLEDColor(i, CYAN);
                else                           setLEDColor(i, OFF);   
        break;
        
        default:
            setUniformColor(MAGENTA);
            setUniformBrightness(0b00001);
        break;
    }
}


/* advance the current color to the next one in line */
void LED_Controller::cycle_color(){
    if(++myColor_index >= MY_PALETTE_SIZE) myColor_index = 0;
}

void LED_Controller::cycle_color_l(){
    if(++leftColor >= MY_PALETTE_SIZE)     leftColor = 0;
}

void LED_Controller::cycle_color_r(){
    if(++rightColor >= MY_PALETTE_SIZE)    rightColor = 0;
}



/* create a gradient on the whole strip */
void LED_Controller::colorGradient(long color1, long color2) {
    colorGradient_fromLeft(color1, color2, myStripPtr->length, 0);
}

/* create a gradient on the left half of the strip */
void LED_Controller::colorGradient_LeftHalf(long color1, long color2) {
    colorGradient_fromLeft(color1, color2, (myStripPtr->length/2), 0);
}

/* create a gradient on the right half of the strip */
void LED_Controller::colorGradient_RightHalf(long color1, long color2) {
    colorGradient_fromLeft(color1, color2, myStripPtr->length/2, myStripPtr->length/2);
}





/* create a color gradient across NUM leds, starting at some index specified by OFFSET */
void LED_Controller::colorGradient_fromLeft(long color1, long color2, int num, int offset){
    unsigned char R_Left = (color1>>16);
    unsigned char G_Left = (color1>>8);
    unsigned char B_Left = (color1);
    
    unsigned char R_Right = (color2>>16);
    unsigned char G_Right = (color2>>8);
    unsigned char B_Right = (color2);
    
    float r_diff = (R_Right - R_Left) / num;
    float g_diff = (G_Right - G_Left) / num;  
    float b_diff = (B_Right - B_Left) / num; 

    for(int i=0; i<num; i++)
        setLEDColor_Bytes(i+offset, (R_Left+ i*r_diff), (G_Left+ i*g_diff), (B_Left+ i*b_diff));
}


/* fade from color 1 to color 2 */  
void LED_Controller::fade_into_color(long color1, long color2){
    unsigned char R_Old = (color1>>16);
    unsigned char G_Old = (color1>>8);
    unsigned char B_Old = (color1);
    
    unsigned char R_New = (color2>>16);
    unsigned char G_New = (color2>>8);
    unsigned char B_New = (color2);
    
    float r_diff = (R_New - R_Old) / FADE_STEPS;
    float g_diff = (G_New - G_Old) / FADE_STEPS;  
    float b_diff = (B_New - B_Old) / FADE_STEPS; 

    for(int i=0; i<FADE_STEPS; i++){
        setUniformColor_Bytes( (R_Old + i*r_diff), (G_Old+ i*g_diff), (B_Old+ i*b_diff) );
        showLEDStrip();
        delay(FADE_STEP_DELAY);
    }
    
    setUniformColor(color2);
}