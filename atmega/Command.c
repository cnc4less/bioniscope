#include <avr/io.h>
#include <avr/interrupt.h>
#include "Global.h"
#include "BTUSART.h"
#include "Pots.h"
#include "Sampler.h"

Byte Command  = 0x0A; // Most recently received command
Byte Data1	  = 0x00; // First optional data byte sent with Command
Byte Data2	  = 0x00; // Second optional data byte sent with Command

// Setup command interface
void CommandSetup(void) {
  // Initialise bluetooth
  BTUSARTInit();
}

// Receive command
void ReceiveCommand(void) {
  // Received command
  Command = BTUSARTRead();

  // Commands we need to receive more data on
  switch (Command) {
	// Set potentiometer value in amplifier
	case 0x08:
	  Data1 = BTUSARTRead();
	  break;

	default:
	  break;
  }
}

// Respond to commands
void CommandRun(void) {
  int i;

  // Check serial data
  ReceiveCommand();

  // Respond differently based on command
  switch(Command) {
	// Noop
	case 0x0A:
	  break;

	// Set potentiomer resistance
	// 7LSB for value
	// MSB ? (channel B) : (channel A)
	case 0x08:
	  // PotsSet takes care of everything for us
	  // TODO Make pots work
	  // PotsSet(Data1);
	  BTUSARTTransmit(Data1);
	  break;

	// Return digital samples
	case 0x02:
	  for (i=0; i<NUM_SAMPLES; i++) { BTUSARTTransmit(DigitalSamples[i]); }
	  break;

	// Return error
	default:
	  BTUSARTTransmit(0xFF);
	  break;
  }

  // Reset command back to noop
  Command = 0x0A;

  // Return a newline
  BTUSARTTransmit(0x0A);
}
