#include "mbed.h"
#include "arm_book_lib.h"

#include "windshield_wipers_subsystem.h"

#define PERIOD 0.02

AnalogIn modeSelect(A0);
AnalogIn delaySelect(A1);

PwmOut servo(PF_9);

void windshieldWipersInit()
{
    servo.period(PERIOD);
}

void windshieldWipersUpdate() {
    
}