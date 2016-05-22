// Helpers for working with Attiny2313

// Cleaner setting of bits
#define BV(x) (1<<x)

namespace Attiny2313 {

/// Possible prescaler values for timers.
enum TimerPrescalerValue {
    PSV_1,
    PSV_8,
    PSV_64,
    PSV_256,
    PSV_1024
};

/// Sets timer 0 prescaler to requested value.
///
/// This function assumes that Clock Select bits have not been touched yet. Note
/// that timer 0 does not support all Timer0PrescalerValue values. If illegal
/// value is entered, prescaler is not set to any value.
///
/// \param value
///    Requested prescaler value
void setTimer0Prescaler(TimerPrescalerValue value);

}