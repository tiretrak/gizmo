////// Copyright 2016 by Sean Luke
////// Licensed under the Apache 2.0 License



#ifndef __MIDI_INTERFACE__
#define __MIDI_INTERFACE__

//// MIDI CHANNELS
#define CHANNEL_OFF 0
#define CHANNEL_OMNI 17                         // For INPUT
#define NUM_MIDI_CHANNELS 16
#define LOWEST_MIDI_CHANNEL 1
#define HIGHEST_MIDI_CHANNEL 16


//// MIDI CLOCK OPTIONS SETTINGS
// We have five options for handling the MIDI clock (or producing our own)
// These are the possible settings for options.clock

#define USE_MIDI_CLOCK 0         // Use external MIDI clock, and pass it through
#define CONSUME_MIDI_CLOCK 1     // Use external MIDI clock, but don't pass it through
#define IGNORE_MIDI_CLOCK 2      // Use our own internal clock, but pass any MIDI clock through
#define GENERATE_MIDI_CLOCK 3    // Use our own internal clock and emit a MIDI clock from it, rather than passing through any MIDI clock
#define BLOCK_MIDI_CLOCK 4       // Use our own internal clock.  Don't pass through or emit any MIDI clock.


// Some useful predicates
#define USING_EXTERNAL_CLOCK() (options.clock <= CONSUME_MIDI_CLOCK)	// are we using any external clock?




// in midi_Defs.h there is an enum with various MIDI commands. 
// I have to use a few of them to pass in clock commands, but I 
// don't like the enum names ("Clock", "Stop", etc.) which are too
// simple and collide with other symbols of mine.  So here I have 
// defined some #defines to do the same thing.

#define    MIDIClock                 ((midi::MidiType) 0xF8)    ///< System Real Time - Timing Clock
#define    MIDIStart                 ((midi::MidiType) 0xFA)    ///< System Real Time - Start
#define    MIDIContinue              ((midi::MidiType) 0xFB)    ///< System Real Time - Continue
#define    MIDIStop                  ((midi::MidiType) 0xFC)    ///< System Real Time - Stop
#define    MIDIInvalidType           ((midi::MidiType) 0x00)    ///< For notifying errors
#define    MIDINoteOff               ((midi::MidiType) 0x80)    ///< Note Off
#define    MIDINoteOn                ((midi::MidiType) 0x90)    ///< Note On
#define    MIDIAfterTouchPoly        ((midi::MidiType) 0xA0)    ///< Polyphonic AfterTouch
#define    MIDIChannelControl        ((midi::MidiType) 0xB0)    ///< Control Change / Channel Mode
#define    MIDIProgramChange         ((midi::MidiType) 0xC0)    ///< Program Change
#define    MIDIAfterTouchChannel     ((midi::MidiType) 0xD0)    ///< Channel (monophonic) AfterTouch
#define    MIDIPitchBend             ((midi::MidiType) 0xE0)    ///< Pitch Bend
#define    MIDISystemExclusive       ((midi::MidiType) 0xF0)    ///< System Exclusive
#define    MIDITimeCodeQuarterFrame  ((midi::MidiType) 0xF1)    ///< System Common - MIDI Time Code Quarter Frame
#define    MIDISongPosition          ((midi::MidiType) 0xF2)    ///< System Common - Song Position Pointer
#define    MIDISongSelect            ((midi::MidiType) 0xF3)    ///< System Common - Song Select
#define    MIDITuneRequest           ((midi::MidiType) 0xF6)    ///< System Common - Tune Request
#define    MIDIActiveSensing         ((midi::MidiType) 0xFE)    ///< System Real Time - Active Sensing
#define    MIDISystemReset           ((midi::MidiType) 0xFF)    ///< System Real Time - System Reset







/// ALL ITEM TYPES
/// itemType can be any of the following

// These are grouped first -- they're the "fast MIDI" messages and have some FALL THRUs, see STATE_GAUGE
#define MIDI_CLOCK                      0
#define MIDI_TIME_CODE          1
#define MIDI_ACTIVE_SENSING     2

// These are the channel messages and must be grouped together, see the >= and <= in STATE_GAUGE
#define MIDI_NOTE_ON   3
#define MIDI_NOTE_OFF    4
#define MIDI_AFTERTOUCH 5
#define MIDI_AFTERTOUCH_POLY 6
#define MIDI_PROGRAM_CHANGE     7
#define MIDI_PITCH_BEND 8
#define MIDI_CC_7_BIT    9                // simple CC messages
#define MIDI_CC_14_BIT    10              // all other CC messages other than NRPN, RPN
#define MIDI_NRPN_14_BIT    11            // NRPN DATA messages
#define MIDI_RPN_14_BIT    12             // RPN DATA messages
#define MIDI_NRPN_INCREMENT    13
#define MIDI_RPN_INCREMENT    14
#define MIDI_NRPN_DECREMENT    15
#define MIDI_RPN_DECREMENT    16
// End Group

// Other messages
#define MIDI_SYSTEM_EXCLUSIVE   17
#define MIDI_SONG_POSITION      18
#define MIDI_SONG_SELECT        19
#define MIDI_TUNE_REQUEST       20
#define MIDI_START      21
#define MIDI_CONTINUE   22
#define MIDI_STOP       23
#define MIDI_SYSTEM_RESET       24



// newItem can be any of the following
#define NO_NEW_ITEM 0
#define NEW_ITEM 1
#define WAIT_FOR_A_SEC 2        // indicates that LSB data might be coming through any minute now.  Or not.


// NEW INCOMING MIDI DATA STORAGE
extern uint8_t  newItem;				// Is there an item?  NO_NEW_ITEM (0), NEW_ITEM (1), or WAIT_FOR_A_SEC (2)
extern uint8_t  itemType;				// What kind of MIDI item is it?  one of Item Types above
extern uint16_t itemNumber;             // Note on/off/poly aftertouch use this for NOTE PITCH, otherwise it's the parameter for PC/CC/NRPN/RPN
extern uint16_t itemValue;              // Note on/off use this for NOTE VELOCITY, poly and channel aftertouch uses this for PRESSURE, otherwise it's the value for PC/CC/NRPN/RPN/PITCH BEND
extern uint8_t itemChannel;				// Channel of the incoming item.  One of 1...16

#ifdef INCLUDE_PROVIDE_RAW_CC
	extern uint8_t midiInProvideRawCC;
#endif




//// REMOTE CONTROL VIA NRPN or CC

// The following NRPN or CC parameters will control Gizmo.
// Buttons (including BYPASS and UNLOCK) are 1 when pressed, 0 when unpressed.
// Pots should be sent 14-bit, but only range from 0...1023 inclusive

#define NRPN_LEFT_POT_PARAMETER                 0
#define NRPN_RIGHT_POT_PARAMETER                1
#define NRPN_BACK_BUTTON_PARAMETER              2
#define NRPN_MIDDLE_BUTTON_PARAMETER            3
#define NRPN_SELECT_BUTTON_PARAMETER            4
#define NRPN_BYPASS_PARAMETER                   5
#define NRPN_UNLOCK_PARAMETER                   6
#define NRPN_START_PARAMETER                    7
#define NRPN_STOP_PARAMETER                     8       
#define NRPN_CONTINUE_PARAMETER                 9

// The Pot CC parameters are 14-bit (MSB+LSB).  The others are 7-bit.

#define CC_LEFT_POT_PARAMETER                 14
#define CC_RIGHT_POT_PARAMETER                15
#define CC_BACK_BUTTON_PARAMETER              102
#define CC_MIDDLE_BUTTON_PARAMETER            103
#define CC_SELECT_BUTTON_PARAMETER            104
#define CC_BYPASS_PARAMETER                   105
#define CC_UNLOCK_PARAMETER                   106
#define CC_START_PARAMETER                    107
#define CC_STOP_PARAMETER                     108     
#define CC_CONTINUE_PARAMETER                 109




//// MIDI HANDLERS

void handleStart();
void handleStop();
void handleContinue();
void handleClock();
void handleNoteOff(byte channel, byte note, byte velocity);
void handleNoteOn(byte channel, byte note, byte velocity);
void handleAfterTouchPoly(byte channel, byte note, byte pressure);
void handleGeneralControlChange(byte channel, byte number, byte value);
void handleProgramChange(byte channel, byte number);
void handleAfterTouchChannel(byte channel, byte pressure);
void handlePitchBend(byte channel, int bend);
void handleTimeCodeQuarterFrame(byte data);
void handleSystemExclusive(byte* array, unsigned size);
void handleSongPosition(unsigned beats);
void handleSongSelect(byte songnumber);
void handleTuneRequest();
void handleActiveSensing();
void handleSystemReset();


//// SENDING MIDI
void sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel);
void sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel);
void sendPolyPressure(uint8_t note, uint8_t pressure, uint8_t channel);
void sendAllNotesOffDisregardBypass();
void sendAllNotesOff();


//// SENDING VOLTAGE
void setPrimaryVoltage(uint8_t voltage, uint8_t on);
void setSecondaryVoltage(uint8_t voltage);
void turnOffVoltage();


#endif __MIDI__
