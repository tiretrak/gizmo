////// Copyright 2016 by Sean Luke
////// Licensed under the Apache 2.0 License




////// ALL.H
//////
////// This is just distributing #include file.  Everyone #includes All.h

// This little dance allows me to test for Uno code while on a Mega, in case I don't
// have an Uno around, simply by by commenting out the #define __MEGA__ line
#if defined (__AVR_ATmega2560__)
#define __MEGA__
#endif __AVR_ATmega2560__

#if defined (__AVR_ATmega328P__)
#define __UNO__
#endif __AVR_ATmega328P__


// You'll see GLOBAL here and there.  It means nothing -- but it makes it easy
// for me to grep for global variables.
#define GLOBAL

// If this is set, then gizmo will start up in bypass mode initially, AND
// every time you leave the toplevel menu and enter an application, gizmo
// will always exit bypass mode even if you had manually set it.
//
// If this is UNSET, then gizmo will not start up in bypass mode initially,
// and will not toy with bypass mode at all in the toplevel -- it stays as you set it.
#define TOPLEVEL_BYPASS


// If you don't want to use the SparkFun MIDI Shield, and perhaps use some other
// compatible MIDI shield without the buttons and pots, you can turn on these defines.
// Don't turn BOTH of them on at the same time!
//
// IF you turn on this define and then run the code on the Arduino, it will reset the options,
// display the splash screen, then display RSET and nothing else.  This makes it possible to do
// a reset without holding the three buttons down (because you have no buttons!) 
//#define HEADLESS_RESET
//
// If you turn on this define, Gizmo will eliminate the option of OFF for its MIDI Control so you
// can't possibly lock yourself out by accident.  You can then control Gizmo entirely via NRPN
// without ever touching the knobs or buttons (which you might not have).
//#define HEADLESS



/////// SETTABLE APPLICATIONS AND FEATURES
///
/// The following applications, options, and additional features can be turned on or off depending
/// on your space needs.  However in order to modify the applications and options you will ALSO need
/// to modify certain menu arrays so they match properly.


// -- APPLICATIONS --
// Note that if you include or exclude certain of these you must also take care to set up the menuItems array
// correctly in STATE_ROOT (see roughly lines 1023--1029 of TopLevel.cpp)
// 
// INCLUDE_ARPEGGIATOR				Include the "basic" Arpeggiator application (the one which appears in the Uno)
// INCLUDE_STEP_SEQUENCER			Include the "basic" Step Sequencer application (the one which appears in the Uno)
// INCLUDE_RECORDER					Include the "basic" note recorder application (the one which appears in the Uno)
// INCLUDE_GAUGE					Include the "basic" MIDI Gauge application
// INCLUDE_CONTROLLER				Include the "basic" Controller application (the one which appears in the Uno)
// INCLUDE_SPLIT					Include the Keyboard Split application
// INCLUDE_THRU						Include the Thru application
// INCLUDE_MEASURE					Include the Measure Counter application


// -- ADDITIONAL FEATURES --
// These are turned on as a consequence of other features -- they're probably not useful to turn on yourself.
// INCLUDE_EXTENDED_FONT					Should the extended font be made available?  This currently consists of some extra LFO wave shapes
// INCLUDE_SEND_NULL_RPN					Should we terminate NRPN/RPN messages with two additional CCs?  Better but slower.

// -- EXPERIMENTAL JUNK --
// INCLUDE_CONTROL_BY_NOTE					[In development] Should we allow control of Gizmo by playing notes on the Control channel?
// INCLUDE_STEP_SEQUENCER_CC_MUTE_TOGGLES	[In development] Should we toggle mutes in the step sequencer?

// -- OPTIONS --
// USE_ALL_NOTES_OFF						These define how Gizmo kills all sounds.  The Blofeld's Arpeggiated sounds do not respond properly 
// USE_ALL_SOUNDS_OFF						to All Notes Off.  But other hardware, such as the Kawai K4, doesn't properly respond to ALL Sounds 
//											Off.  :-(  You can set one, or both, of these.

#define USE_ALL_SOUNDS_OFF					// see Mega below, it uses both


/// Here are the standard values for the MEGA and for the UNO

#if defined(__MEGA__)
#define INCLUDE_ARPEGGIATOR
#define INCLUDE_STEP_SEQUENCER
#define INCLUDE_RECORDER
#define INCLUDE_GAUGE
#define INCLUDE_CONTROLLER
#define INCLUDE_SPLIT
#define INCLUDE_THRU
#define INCLUDE_SYNTH
#define INCLUDE_MEASURE

//// NOTE: To include the Sysex dump facility, you not only uncomment the INCLUDE_SYSEX line below, but
//// you ALSO must go into the "midi_Settings.h" file in the Forty Seven Effects MIDI library and change the line 
////    static const unsigned SysExMaxSize = 1;		// this should never be 0 due to a library bug
//// to
////	static const unsigned SysExMaxSize = 787;   // the size of the MIDI Dump of a Slot

//#define INCLUDE_SYSEX

#endif __MEGA__






#if defined(__UNO__)

// This is a useful set
#define INCLUDE_ARPEGGIATOR
#define INCLUDE_STEP_SEQUENCER
#define INCLUDE_RECORDER
#define INCLUDE_CONTROLLER

// You can include these but one or more other items will have to be jettisoned as a result.
// IMPORTANT NOTE: If you include another application or a different one will also have to modify 
// The menu array on around Line 616 of TopLevel.cpp, where it states which applications are available.
// You need to make sure that the array length stays correct (for example, it says menuItems[5],
// and if you remove an app, it needs to say menuItems[4]).  Similarly, the second argument in doMenuDisplay(...)
// (currently a 5) would need to change to a 4.
//
// Whatever applications you install need to be ordered in this order in that menu:
// Arpeggiator, Step Sequencer, Recorder, Gauge, Controller, Split, Thru, Synth, Measure, Sysex, [Options]

// --- Additional applications
// #define INCLUDE_GAUGE
// #define INCLUDE_SPLIT
// #define INCLUDE_THRU
// #define INCLUDE_SYNTH
// #define INCLUDE_MEASURE

// -- Additional Global features
// Sysex isn't an available option on the Uno: it doesn't have enough memory

#endif __UNO__




// Below are dependencies

#ifdef INCLUDE_SYNTH
#define INCLUDE_SYNTH_WALDORF_BLOFELD
#define INCLUDE_SYNTH_KAWAI_K4
#define INCLUDE_SYNTH_KAWAI_K5
#define INCLUDE_SYNTH_OBERHEIM_MATRIX_1000
#define INCLUDE_SYNTH_KORG_MICROSAMPLER
#define INCLUDE_SYNTH_YAMAHA_TX81Z
#endif INCLUDE_SYNTH







#include <Arduino.h>
#include <EEPROM.h>
#include <MIDI.h>
#include <SoftReset.h>
#include "MidiInterface.h"
#include "Utility.h"
#include "TopLevel.h"
#include "MidiShield.h"
#include "LEDDisplay.h"
#include "Division.h"
#include "Timing.h"
#include "Control.h"
#include "Storage.h"
#include "Arpeggiator.h"
#include "Recorder.h"
#include "Options.h"
#include "StepSequencer.h"
#include "Gauge.h"
#include "Split.h"
#include "Thru.h"
#include "Measure.h"
#include "Synth.h"

// This lets everyone have access to the MIDI global, not just
// the .ino file
extern midi::MidiInterface<HardwareSerial> MIDI; 

