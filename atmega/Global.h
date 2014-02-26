typedef unsigned char Byte;
#define NUM_SAMPLES 1024 // Number of samples to take

#ifndef _TD_DEFINED
  #define _TD_DEFINED = 1
  extern int AnalogueTimeDelay;
  extern int DigitalTimeDelay;
  extern Byte DigitalTriggerThreshold;
  extern Byte DigitalTriggerType;
#endif
