/* 
 * controller.cpp
 * chris hamby
 * 
 * here you'll find the controller constructor
 * and the top-level controller operating system
*/

#include <Arduino.h>
#include "led_controller.h"
//#include "colors.h"
//#include "led_strip.h"
//#include "led_midi.h"
#include "config.h"
#include "patterns.h"
#include "programs.h"


void LED_Controller::init_controller(){
    CurrentProgram = DEFAULT_PROGRAM;
    CurrentPattern = DEFAULT_PATTERN;
    program_initialized = 0;

    MY_PALETTE      = DEFAULT_PALETTE;
    MY_PALETTE_SIZE = DEFAULT_PALETTE_SIZE;

    myColor_index = 0;
    leftColor = 0;
    rightColor = 1;

    num_leds = myStripPtr->length;
}


/*
 *  This is, ideally, the only function called in main
 *  There could be interrupts to add button control,
 *  or analog reads to add potentiometer control,
 *  but don't even think about adding new main code >:-O
 */
int LED_Controller::LED_STRIP_RUNNER(){
    switch(CurrentProgram){

        case EQUALIZER:
            #ifdef ENABLE_EQUALIZER
                run_equalizer();
            #else
                cycle_strip_program();
            #endif
        break;
        
        case MIDI_SERIAL: 
            #ifdef ENABLE_MIDI_SERIAL
                read_my_midi_data();
                #else
                cycle_strip_program();
            #endif
        break;

        case MIDI_PROGRAM_1:
            #ifdef ENABLE_MIDI_PROGRAM_1
                run_midi_program_1();
                #else
                cycle_strip_program();
            #endif
        break;

        

        case COOL_LIGHT:
            #ifdef ENABLE_COOL_LIGHT
                run_single_color(WHYTE);
            #else
                cycle_strip_program();
            #endif
        break;

        case WARM_LIGHT:
            #ifdef ENABLE_WARM_LIGHT
                run_single_color(PINK);
            #else
                cycle_strip_program();
            #endif
        break;

        case NEUTRAL_LIGHT:
            #ifdef ENABLE_NEUTRAL_LIGHT
                run_single_color(0xFFE0A0);
            #else
                cycle_strip_program();
            #endif
        break;

        case SHOW_COLOR_1:
            #ifdef ENABLE_COLOR_1
                run_single_color(COLOR_1);
            #else
                cycle_strip_program();
            #endif
        break;
        
        case SHOW_COLOR_2:
            #ifdef ENABLE_COLOR_2
                run_single_color(COLOR_2);
            #else
                cycle_strip_program();
            #endif
        break;
        
        case SHOW_COLOR_3:
            #ifdef ENABLE_COLOR_3
                run_single_color(COLOR_3);
            #else
                cycle_strip_program();
            #endif
        break;
        
        case SHOW_COLOR_4:
            #ifdef ENABLE_COLOR_4
                run_single_color(COLOR_4);
            #else
                cycle_strip_program();
            #endif
        break;
        
        case SHOW_COLOR_5:
            #ifdef ENABLE_COLOR_5
                run_single_color(COLOR_5);
            #else
                cycle_strip_program();
            #endif
        break;

        case SHOW_COLOR_6:
            #ifdef ENABLE_COLOR_6
                run_single_color(COLOR_6);
            #else
                cycle_strip_program();
            #endif
        break;

        case LEFT_SHIFT:
            #ifdef ENABLE_LEFT_SHIFT
                run_left_shift();
            #else
                cycle_strip_program();
            #endif
        break;

        case RIGHT_SHIFT:
            #ifdef ENABLE_RIGHT_SHIFT
                run_right_shift();
            #else
                cycle_strip_program();
            #endif
        break;

        case LEFT_SHIFT_MIRROR:
            #ifdef ENABLE_LEFT_SHIFT_MIRROR
                run_mirror_left_shift();
            #else
                cycle_strip_program();
            #endif
        break;

        case RIGHT_SHIFT_MIRROR:
        #ifdef ENABLE_RIGHT_SHIFT_MIRROR
                run_mirror_right_shift();
            #else
                cycle_strip_program();
            #endif
        break;

        case RIGHT_SHIFT_PALETTE:
            #ifdef ENABLE_RIGHT_SHIFT_PALETTE
                run_right_shift_palette();
            #else
                cycle_strip_program();
            #endif
        break;
        
        case ICE_SPARKLE:
            #ifdef ENABLE_ICE_SPARKLER
                run_ice_sparkle();
            #else
                cycle_strip_program();
            #endif
        break;

        case FADER:
            #ifdef ENABLE_FADER
                run_color_fader();
            #else
                cycle_strip_program();
            #endif
        break;
        
        default:
            //something didn't happen 
            return 0;
    }
    // something happened
    return 1;
}


