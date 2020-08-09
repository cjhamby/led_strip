/* 
 * led_strip.cpp
 * chris hamby
 * last edit: 6 Aug 2020 
 * 
 * functions to access/change data held in LED nodes
 * and to move around the "true" beginning of strip
*/

#include <Arduino.h>
#include "led_strip.h"

//parametrized constructor only 
LED_STRIP::LED_STRIP(int numLEDS){
    /*
     * the data for the led color/brightness is arranged into a circular linked list
     * STRIP_BEGINNING is the node treated as the beginning of the strip
     * SHIFT_OFFSET keeps track of where the "original" beginning is 
    */
    STRIP_BEGINNING =       (LED_NODE*)malloc(sizeof(LED_NODE));
    STRIP_BEGINNING->myData = (LED_PTR)malloc(sizeof(LED_DATA));
    shift_offset = 0;
    length = numLEDS;

    /* create the linked list */
    STRIP_END = STRIP_BEGINNING;
    for(int i=0; i<length-1; i++)
        STRIP_END = add_LED_Node_To_Bottom(STRIP_END);
    
    STRIP_END->nextData = STRIP_BEGINNING; /* close the circular linked list */
    STRIP_BEGINNING->prevData = STRIP_END;
}



// get the node's data pointer at the specified index 
LED_PTR LED_STRIP::get_data_at_index(int index){
    LED_NODE* n = get_node_at_index(index);
    LED_PTR d = n->myData;
    return d;
}



// get the node at the specified index 
LED_NODE* LED_STRIP::get_node_at_index(int index){
    LED_NODE* n = STRIP_BEGINNING; 
    for(int i=0; i<index; i++)
        n = n->nextData;
    return n;
}


LED_NODE* LED_STRIP::get_beginning(){
    return STRIP_BEGINNING;
};


/*   manipulate the "beginning" pointer to shift the strip "left"   */
void LED_STRIP::shift_strip_left(){
    STRIP_BEGINNING = STRIP_BEGINNING->nextData;
    STRIP_END = STRIP_END ->nextData;
    if(++shift_offset>=length) shift_offset =0;
}



/*   manipulate the "beginning" pointer to shift the strip "right"   */
void LED_STRIP::shift_strip_right(){
    STRIP_END = STRIP_BEGINNING;
    for(int i=0; i<length-2; i++)   
        STRIP_END = STRIP_END->nextData;
    STRIP_BEGINNING = STRIP_END->nextData; 
    if(--shift_offset<0)   shift_offset = length-1;
}





void LED_STRIP::copy_LED_Node(LED_NODE* src, LED_NODE* dest){
    dest->myData->BRIGHTNESS = src->myData->BRIGHTNESS;
    dest->myData->R_VALUE    = src->myData->R_VALUE;
    dest->myData->G_VALUE    = src->myData->G_VALUE;
    dest->myData->B_VALUE    = src->myData->B_VALUE;
}



//put the next node on the bottom (rightmost) of the strip
//return the new "end of list"
LED_NODE* LED_STRIP::add_LED_Node_To_Bottom(LED_NODE* currentEnd){
    LED_NODE* newNode = (LED_NODE*)malloc(sizeof(LED_NODE));
    newNode->myData   = (LED_PTR)malloc(sizeof(LED_DATA));
    currentEnd->nextData = newNode;
    newNode->prevData = currentEnd;
    newNode->nextData = nullptr;
    return newNode;
}