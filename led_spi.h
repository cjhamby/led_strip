/* 
 * led_spi.h
 * chris hamby
 *
 * macros used in spi communication
 * 
*/

#ifndef LED_SPI_H
#define LED_SPI_H

#define EMPTY_BYTE        0x00
#define QUARTER_BYTE      0x40
#define HALF_BYTE         0x80
#define FULL_BYTE         0xFF
#define LED_INIT          0b11100000

#define SPI_DELAY             100   //time between begin() and beginTransaction()
#define DELAY_BETWEEN_FRAMES  1     //this is the delay between LED FRAMEs being passed to the strip -> see showLEDStrip()
#define DELAY_BETWEEN_COLORS  3000  //this is the delay for colorPulse()

#define SPI_FREQUENCY     (1000000)   //1 MHz
#define DATA_ORIENTATION  MSBFIRST
#define SPI_MODE          SPI_MODE0

#endif