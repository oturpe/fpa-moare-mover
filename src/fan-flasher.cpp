// Fog mover tester

#include "Attiny2313Utils.h"

#include "config.h"

#include <avr/io.h>
#include <util/delay.h>

// \brief
///    Turns the indicator led on of off
///
/// \param lit
///    If led is turned on. Otherwise it is turned off.
inline void setIndicator(bool lit) {
    if (lit) {
        PORTB |= BV(PORTB4);
    }
    else {
        PORTB &= ~BV(PORTB4);
    }
}

// \brief
///    Advances the motor half a step
inline void halfStep() {
    static bool high;

    high = !high;
    if (high) {
        PORTB |= BV(PORTB2);
    }
    else {
        PORTB &= ~BV(PORTB2);
    }
}

// \brief
///    Advances the motor half a step
///
/// \papar clockwise
///    If the new direction is clockwise
inline void setDirection(bool clockwise) {
    if (clockwise) {
        PORTB |= BV(PORTB1);
    }
    else {
        PORTB &= ~BV(PORTB1);
    }
}

int main() {

    // Set output pins
    //    B7 (indicator)
    //    B1 (motor direction)
    //    B2 (motor step)
    DDRB |= BV(DDB4) | BV(DDB1) | BV(DDB2);

    bool indicatorLit = false;
    bool clockwise = false;
    uint64_t counter = 0;

    while(true) {
        counter += 1;
        _delay_ms(LOOP_DELAY);

        if(counter % INDICATOR_HALF_PERIOD == 0) {
            indicatorLit = !indicatorLit;
            setIndicator(indicatorLit);
        }

        if(counter % STEP_HALF_PERIOD == 0) {
            halfStep();
        }

        if (counter % DIRECTION_PERIOD == 0) {
            clockwise = !clockwise;
            setDirection(clockwise);
        }
    }
}
