/* 
 * spi.cpp
 * chris hamby
 * last edit: 6 Aug 2020 
 * 
 * functions to communicate with the strip using SPI
 * to communicate with the strip, we send:
 *   [start frame] -- num_leds*[data frame] -- [end frame]
*/

#include <Arduino.h>
#include <SPI.h>
#include "led_strip.h"
#include "led_spi.h"
#include "led_controller.h"


// I didn't write the SPI file so don't ask me...
// but this defines the parameters used in SPI communication
SPISettings mySettings(SPI_FREQUENCY, DATA_ORIENTATION, SPI_MODE);


/*
 * send the LED strip start frame
 * the start frame is a whole bunch of zeroes
 */
void sendStartFrame(){
    SPI.begin();
    delayMicroseconds(SPI_DELAY); // just in case SPI.begin needs time to set up?
    SPI.transfer(EMPTY_BYTE);
    SPI.transfer(EMPTY_BYTE);
    SPI.transfer(EMPTY_BYTE);
    SPI.transfer(EMPTY_BYTE);
}



/* 
 * send data from an LED node
 * the first byte is: 11100000 + 000[brightness]
 * brightness is a 5 bit value 
 * 
 * CALL SendStartFrame() FIRST!
 * SPI IS NOT ENABLED OTHERWISE 
*/
void sendLEDData(LED_NODE* thisLEDnode){
    LED_PTR thisLED = thisLEDnode -> myData;      
    byte firstByte = LED_INIT | (thisLED->BRIGHTNESS);
    SPI.transfer(firstByte);
    SPI.transfer(thisLED->B_VALUE);
    SPI.transfer(thisLED->G_VALUE);
    SPI.transfer(thisLED->R_VALUE);
}



/*
 * send the LED strip end frame
 * the end frame is a whole bunch of 1's
*/
void sendEndFrame(){
    SPI.transfer(FULL_BYTE);
    SPI.transfer(FULL_BYTE);
    SPI.transfer(FULL_BYTE);
    SPI.transfer(FULL_BYTE);
    SPI.endTransaction();
    SPI.end();
}



/*
 * this function handles all SPI transmissions
 * it sends [start] [data] [end]
*/
void LED_Controller::showLEDStrip(){
    LED_NODE* currentNode = myStripPtr->get_beginning();
    sendStartFrame();
    for(int i=0; i<num_leds; i++){
        sendLEDData(currentNode);
        currentNode = currentNode->nextData;
    }
    sendEndFrame();
}



/*
 * this function handles all SPI transmissions
 * with the added bonus of a mirror-ed strip
*/
void LED_Controller::showMirrorLEDStrip(){
    LED_NODE* currentNode = myStripPtr->get_beginning();
    LED_NODE* mirrorArray[(num_leds)/2];   // holds the second half of the mirrored strip

    sendStartFrame();

    for(int i=0; i<(num_leds/2); i++){    //  Transmit data for half of the LED strip
        sendLEDData(currentNode);       //  Send this node's data to an LED on the first half
        mirrorArray[i] = currentNode;   //  Copy the node's address to the mirror list 
        currentNode = currentNode->nextData;
    }
    
    // now go in reverse through the mirrorArray list
    for(int i=(num_leds/2)-1; i>0; i--)   sendLEDData(mirrorArray[i]);
    sendEndFrame();
}


