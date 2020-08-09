/* 
 * midi.cpp
 * chris hamby
 * last edit: 6 Aug 2020 
 * 
 * midi initialization, reading, and related programs
*/

#include <MIDI.h>
#include "led_midi.h"
#include "led_controller.h"
#include "colors.h"
#include "patterns.h"

/* structs defined in led_midi.h :
 * 
 * MIDI_DATA_HOLDER 
 * - holds the note, velocity, and channel of the latest midi message 
 * 
 * MIDI_PTR 
 * - points to ^
*/


/* holds the most recent midi message data */
MIDI_PTR my_midi_data;


/*
  * I didn't write this function, check it in MIDI.h
  * it is required, though I don't know quite what it does
  * I *think* that MIDI is an instance of a class, i.e. MIDI.begin(__)
*/
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

void initMidi() {
    my_midi_data = (MIDI_PTR)malloc(sizeof(MIDI_DATA_HOLDER));
    MIDI.begin(MIDI_CHANNEL_OMNI); 
    clear_midi_data();  
}

/* enable listening for MIDI messages */ 
void startMidi() { initMidi(); }


/* disable listening for MIDI messages */
void stopMidi() { }



/*
 * MY_MIDI_DATA points to a global MIDI_DATA_HOLDER 
 * Other functions will use the data held in it to perform tasks
 * This function just stores the latest data into it 
*/
int read_midi_data(){
    // a message arrived 
    if(MIDI.read()){
        byte type = MIDI.getType();
        switch (type) {
        // --- NOTE ON ---
        case midi::NoteOn:
            my_midi_data->note     = MIDI.getData1();
            my_midi_data->velocity = MIDI.getData2();
            my_midi_data->channel  = MIDI.getChannel();
            return 1;
            break;
        // --- NOTE OFF ---
        case midi::NoteOff:
            my_midi_data->note     = MIDI.getData1();
            my_midi_data->velocity = NOTE_OFF_VELOCITY;
            my_midi_data->channel  = MIDI.getChannel();
            return 1;
            break;
        // any other type of message is ignored
        default:
            break;
        }
    
    }
    return 0;
}


void clear_midi_data(){
    my_midi_data->channel  = CLEAR_MIDI_DATA;
    my_midi_data->note     = CLEAR_MIDI_DATA;
    my_midi_data->velocity = CLEAR_MIDI_DATA;
}





/*
 * a test to ensure midi functionality works
 * also a good template for future programs 
*/
void LED_Controller::read_my_midi_data(){
  if(!program_initialized) {
    startMidi();
    program_initialized = 1;
  }

  // check if a new message has arrived
  if(read_midi_data()) {
    Serial.print(my_midi_data->note);
    if(my_midi_data->velocity == NOTE_OFF_VELOCITY)  Serial.println("off");
    else                                             Serial.println("on "); 
  }
}



/* change the state of an LED based on a corresponding note */
void LED_Controller::note_to_LED(int note, bool note_on){
  if(note<0 || note>=myStripPtr->length) return;

  if(note_on)  setLEDOn(note);
  else         setLEDOff(note);
}



/* 
 * notes trigger LEDs 
 * the majority of time is spent polling
 * redrawing the strip takes much less priority
*/
void LED_Controller::run_midi_program_1(){
  init_program(NO_PATTERN, CYAN, ALL_OFF);

  /* polling/reading loop */
  for(int i=0; i<10000; i++){
    if(read_midi_data()) { 
      // map the note to an led index 
      int position = my_midi_data->note + NOTE_TO_LED_CONVERSION;
      
      // is the LED turning on or off?
      bool note_on_bool = true;                         
      if(my_midi_data->velocity == NOTE_OFF_VELOCITY)  note_on_bool = false;

      note_to_LED(position, note_on_bool);
    }
  }
  showLEDStrip(); 
}