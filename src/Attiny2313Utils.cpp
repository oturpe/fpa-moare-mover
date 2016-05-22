#include "Attiny2313Utils.h"

#include <avr/io.h>

namespace Attiny2313 {

void setTimer0Prescaler(TimerPrescalerValue value) {
    switch (value) {
    case PSV_1:
        TCCR0B |= BV(CS00);
        break;
    case PSV_8:
        TCCR0B |= BV(CS01);
        break;
    case PSV_64:
        TCCR0B |= BV(CS01) | BV(CS00);
        break;
    case PSV_256:
        TCCR0B |= BV(CS02);
        break;
    case PSV_1024:
        TCCR0B |= BV(CS02) | BV(CS00);
        break;
    default:
        break;
    }
}

}
