/* 
 * led_structs.h
 * chris hamby
 * 
 * structs to represent the led strip and hold data
*/

#ifndef LED_STRUCTS_H
#define LED_STRUCTS_H

typedef struct{
  unsigned char BRIGHTNESS;
  unsigned char R_VALUE;
  unsigned char G_VALUE;
  unsigned char B_VALUE;
}LED_DATA;

typedef LED_DATA* LED_PTR;

typedef struct led_node_struct{       // a node for making a circular linked list 
  LED_PTR myData;                     // this node's data
  struct led_node_struct* prevData;   // previous LED_NODE 
  struct led_node_struct* nextData;   // next LED_NODE
}LED_NODE;


#endif