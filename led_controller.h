/* 
 * controller.h
 * chris hamby
 * 
 * This is the most comprehensive part of the code 
 * 
 * The controller is responsible for:
 * - sending LED data to the strip 
 * - manipulating LED data (i.e. the pattern)
 * - running any program ( functions that change the pattern )
 * 
*/
#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "led_strip.h"
#include "palettes.h"


class LED_Controller{
    public:

    LED_Controller(LED_STRIP* stripPtr){ myStripPtr = stripPtr; };
    int LED_STRIP_RUNNER();
    void init_controller();
    void cycle_strip_program(); 
    void change_current_program(unsigned char);

    private:

    LED_STRIP* myStripPtr;             // the strip being controlled
    unsigned char CurrentPattern;      // info about the linked list data
    unsigned char CurrentProgram;      // what's happening to the linked list data
    unsigned char program_initialized; // when we change programs, we may have to do setup  
    
    int num_leds;

    PALETTE_PTR MY_PALETTE;            // color palette information
    int MY_PALETTE_SIZE;
    int myColor_index;

    long leftColor;           // some programs require different colors for each side
    long rightColor;


    /*
    * SPI.CPP --------------------------------------------------------- 
    * These functions send the LED data to the strip via SPI 
    * they rely on the SPI instantiated in LED_STRIP_SPI.cpp
    */
    void showLEDStrip();
    void showMirrorLEDStrip();


    /*
     * LEDS.CPP ------------------------------------------------------
     * These functions interact with the LED Strip's LED nodes
    */
    void setLEDOn(int);
    void setLEDOff(int);
    void setLEDOn_TrueIndex(int);
    void setLEDOff_TrueIndex(int);
    void setLEDColor(int, long);
    void setLEDColor_Bytes(int, unsigned char, unsigned char, unsigned char);
    void setLEDBrightness(int, unsigned char);
    int dimLED(int);

    /* whole strip functions */
    void setUniformColor(long);
    void setUniformColor_Bytes(unsigned char, unsigned char, unsigned char);
    void setAllOff();
    void setUniformBrightness(unsigned char);


    /*
     * PATTERNS.CPP -------------------------------------------------
     * These functions call the LED functions to change data according to patterns 
    */
    void init_strip();
    void init_strip_off();
    void cycle_color();
    void cycle_color_l();
    void cycle_color_r();
    void colorGradient(long, long);
    void colorGradient_LeftHalf(long, long);
    void colorGradient_RightHalf(long, long);
    void colorGradient_fromLeft(long, long, int, int);
    void fade_into_color(long, long);
    void init_strip_pattern(unsigned char);


    /* PROGRAMS.CPP -------------------------------------------------
     * These are the top-level functions
     * They use PATTERN and LED functions to achieve animation
     * put another way, they use those functions to change the strip in real time
    */
    void init_program(unsigned char, long, unsigned char);
    void run_single_color(long c);
    void run_color_fader();
    void run_ice_sparkle();
    void run_left_shift();
    void run_right_shift();
    void run_mirror_left_shift();
    void run_mirror_right_shift();
    void run_right_shift_palette();
    void run_pot_control();
    void run_equalizer();

    
    /* midi functions*/
    void read_my_midi_data();
    void note_to_LED(int, bool);
    void run_midi_program_1();
};



#endif