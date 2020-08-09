/* 
 * led_strip.h
 * chris hamby
 * 
 * The LED_STRIP class is essentially a container for the linked list, adds a bit of context 
 * the class functions:
 * - interact with nodes
 * - move the "true" beginning of the strip 
 * 
*/

#ifndef LED_STRIP_H
#define LED_STRIP_H

#include "led_structs.h"

class LED_STRIP
{
    LED_NODE* TRUE_BEGINNING;   // for reference; the beginning when the strip is created
    LED_NODE* STRIP_BEGINNING;  // these point to the top/bottom of the (shifted) led list
    LED_NODE* STRIP_END;
    
    
    public:
        LED_STRIP(int);         // default constructor, create strip w/ default values
        long length;            // how many leds are on the strip
        int shift_offset;       // difference between shifted beginning and true beginning

        // These are defined in LED_STRIP.cpp
        void shift_strip_left();        
        void shift_strip_right();
        void copy_LED_Node(LED_NODE*, LED_NODE*);

        LED_NODE* get_beginning();
        LED_NODE* add_LED_Node_To_Bottom(LED_NODE*);
        LED_NODE* get_node_at_index(int);
        LED_PTR   get_data_at_index(int);
};

extern LED_STRIP my_strip;
#endif