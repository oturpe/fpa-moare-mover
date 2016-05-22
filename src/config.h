// Cpu frequency for util/delay.h
#define F_CPU 1000000

// Half of delay in main execution loop, given in milliseconds
#define LOOP_DELAY 10

// Half length of indicator led on-off sequence. In other words, the time
// the indicator is lit and darkened. Given in units of LOOP_DELAY.
#define INDICATOR_HALF_PERIOD 25

// Total angle of rotation of the motor. Given in units of single motor step
// (or microstep if enabled).
#define ROTATION_ANGLE 750

// Speed of rotation, given as a prescaler value and delay of single step. Unit
// is single clock pulse.
#define ROTATION_PRESCALER Attiny2313::PSV_256
#define STEP_HALF_PERIOD 64
