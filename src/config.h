// Cpu frequency for util/delay.h
#define F_CPU 1000000

// Half of delay in main execution loop, given in milliseconds
#define LOOP_DELAY 10

// Half length of indicator led on-off sequence. In other words, the time
// the indicator is lit and darkened. Given in units of LOOP_DELAY.
#define INDICATOR_HALF_PERIOD 25

// The period the motor runs in one direction.
#define DIRECTION_PERIOD 400

// Half length of stepper step sequence. Given in units of LOOP_DELAY.
#define STEP_HALF_PERIOD 4
