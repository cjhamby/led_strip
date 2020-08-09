C++ code to control a strip of addressable APA102 LEDs using a Teensy microcontroller

-------------------------------------------------------------------
 file               header   src          description 
-------------------------------------------------------------------
colors               yes     no           color values and names

config               yes     no           user variables 

hardware             yes     yes          info about hardware (buttons and potentiometers) and interrupts

leds                 no      yes          functions to send instructions to LEDs  

led_controller       yes     yes          controls (i.e. changes) the led strip colors and brightness 

led_midi             yes     yes          midi functions

led_spi              yes     yes          communication with strip 

led_strip            yes     yes          data holder to represent strip 

led_structs          yes     no           data holder to represent single LED 

main                 no      yes          operating system

palettes             yes     yes          color collections

patterns             yes     yes          color arrangements 

programs             yes     yes          animations and other strip procedures





Teensy Default Pins
  SCK ->  13
  CS  ->  10
  DOUT -> 11
  DIN  -> 12
  
From the LED strip data sheet:
  MSB first
  Data transmitted on rising edge
  SPI Frequency -> max 12MHz

The data line is given as 0.7Vdd = 3.5V
But 3.3V seems to work fine...

TIE THE GROUNDS TOGETHER

MIDI Info
RX1  -> 0

Baud: 31250, automatically defined in the MIDI library
