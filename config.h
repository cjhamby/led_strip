/*
 * config.h
 * chris hamby
 * 
 * program enable/disable + variables
*/

#ifndef CONFIG_H_
#define CONFIG_H_

#include "colors.h"
#include "programs.h"
#include "palettes.h"

#define NUM_LEDS 60

#define COLOR_1 YELLOW
#define COLOR_2 ORANGE
#define COLOR_3 GREEN
#define COLOR_4 TEAL
#define COLOR_5 PURPLE
#define COLOR_6 MAGENTA

// uncomment these to enable programs! 
#define ENABLE_LEFT_SHIFT
#define ENABLE_COOL_LIGHT
#define ENABLE_NEUTRAL_LIGHT
#define ENABLE_WARM_LIGHT
//#define ENABLE_COLOR_1
//#define ENABLE_COLOR_2
//#define ENABLE_COLOR_3
//#define ENABLE_COLOR_4
//#define ENABLE_COLOR_5
//#define ENABLE_COLOR_6
//#define ENABLE_RIGHT_SHIFT
//#define ENABLE_LEFT_SHIFT_MIRROR
//#define ENABLE_RIGHT_SHIFT_MIRROR
//#define ENABLE_RIGHT_SHIFT_PALETTE
//#define ENABLE_ICE_SPARKLE
//#define ENABLE_FADER
//#define ENABLE_MIDI_SERIAL
//#define ENABLE_MIDI_PROGRAM_1
//#define ENABLE_EQUALIZER

#define LOW_BRIGHTNESS        0b00010
#define DEFAULT_BRIGHTNESS    0b11000
#define HIGH_BRIGHTNESS       0b11110

#define DEFAULT_PROGRAM         LEFT_SHIFT
#define DEFAULT_COLOR           0x00000080
#define DEFAULT_PALETTE         coolPalette
#define DEFAULT_PALETTE_SIZE    COOL_PALETTE_SIZE


/* program variables */
/* delay used when shifting strip in any direction */
#define SHIFT_DELAY              120   
#define FADE_OUT_AMT             2
/* is this used? */
#define GRADIENT_STEPPER_DELAY   1000     

/* values when the strip fades between colors */
#define FADE_STEPS      30
#define FADE_STEP_DELAY 100


/* not currently in use */
#define BRPOT -1
#define RPOT  -1
#define GPOT  -1
#define BPOT  -1
#define BRPOT_SCALE -1
#define POT_DELAY   -1

/*
 * ice sparkle
 * the strip flashes white-blue "ice sparkles"
 * the sparkles alternate locations on the strip 
*/
#define ICESPARKLE_SPACING   4      /* spacing between lit LEDs */
#define ICESPARKLE_DELAY1    200    /* fading speed             */
#define ICESPARKLE_DELAY2    500    /* delay between cycles     */

#endif