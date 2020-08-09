/* 
 * led_midi.h
 * chris hamby
 * 
 * midi info and structs
*/

#ifndef LEDMIDI_H
#define LEDMIDI_H
                    

#define NOTE_TO_LED_CONVERSION (-30)
// this value is put into the midi data holder
// it let programs know when new messages arrive
// update: i'm....unsure of why it was chosen 
#define CLEAR_MIDI_DATA    -3

// allows us to distinguish between note on/note off 
#define NOTE_OFF_VELOCITY  -1
typedef struct{
    int note;
    int velocity;
    int channel;
}MIDI_DATA_HOLDER;

typedef MIDI_DATA_HOLDER* MIDI_PTR;

extern MIDI_PTR my_midi_data;
extern void initMidi();
extern void startMidi();
extern void stopMidi();
extern int  read_midi_data();
extern void clear_midi_data();

#endif