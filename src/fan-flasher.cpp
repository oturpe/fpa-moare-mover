// Fog mover tester

#include "Attiny2313Utils.h"

#include "config.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

bool indicatorLit = false;

// \brief
///    Turns the indicator led on of off
///
/// \param lit
///    If led is turned on. Otherwise it is turned off.
inline void setIndicator(bool lit) {
    indicatorLit = lit;

    if (lit) {
        PORTB |= BV(PORTB4);
    }
    else {
        PORTB &= ~BV(PORTB4);
    }
}

/// \brief
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

uint16_t motorCounter = 0;
bool clockwise = false;
bool homingComplete = false;

// \brief
///    Advances the motor half a step
///
/// \papar clockwise
///    If the new direction is clockwise
inline void setDirection(bool newClockwise) {
    clockwise = newClockwise;

    if (clockwise) {
        PORTB |= BV(PORTB1);
    }
    else {
        PORTB &= ~BV(PORTB1);
    }
}

/// \brief
///    Set up error condition, loop endlessly indicator with double speed.
inline void endInError() {
    // Stop motor motion
    cli();

    uint16_t counter;

    while(true) {
        counter += 1;
        _delay_ms(LOOP_DELAY);

        if(counter % (INDICATOR_HALF_PERIOD/2) == 0) {
            setIndicator(!indicatorLit);
        }
    }
}

ISR(TIMER0_COMPA_vect, ISR_NOBLOCK) {
    halfStep();
    motorCounter++;

    // The first phase of movement is to find the start position. Until that,
    // the motor keep running in counter-clockwise direction.
    if (!homingComplete) {

        if (motorCounter > (6*ROTATION_ANGLE)/5) {
            endInError();
        }

        return;
    }

    if (motorCounter == ROTATION_ANGLE) {
        setDirection(!clockwise);
        motorCounter = 0;
    }
    else {
    }
}

int main() {

    // Set output pins
    //    B7 (indicator)
    //    B1 (motor direction)
    //    B2 (motor step)
    //    B3 (motor sensor)
    DDRB |= BV(DDB4) | BV(DDB1) | BV(DDB2) | BV(DDB3);

    // Initialize timer interrupt
    TCCR0A |= BV(WGM01);
    TIMSK |= BV(OCIE0A);
    Attiny2313::setTimer0Prescaler(ROTATION_PRESCALER);

    // Set rotation speed.
    OCR0A = STEP_HALF_PERIOD;

    // Initialize pullup for sensor pin
    PORTB |= BV(PORTB3);

    sei();

    uint64_t counter = 0;

    while(true) {
        counter += 1;
        _delay_ms(LOOP_DELAY);

        if(counter % INDICATOR_HALF_PERIOD == 0) {
            setIndicator(!indicatorLit);
        }

        if (!(PINB & BV(PINB3))) {
            homingComplete = true;
            motorCounter = 0;
            setDirection(true);
        }
    }
}
