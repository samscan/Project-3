#include "mbed.h"
#include "arm_book_lib.h"

#include "windshield_wiper_subsystem.h"
#include "servoMotor.h"

#define TIME_INCREMENT_MS           10
#define HI_MODE_MAX                 0.25
#define LOW_MODE_MAX                0.50
#define INT_MODE_MAX                0.75
#define OF_MODE_MAX                 1.00
#define SHORT_MODE_MAX              0.33
#define MEDIUM_MODE_MAX             0.67
#define LONG_MODE_MAX               1.00

AnalogIn modeSelect(A0);
AnalogIn delaySelect(A1);

float getPotentiometerValue(AnalogIn potentiometer);

float getPotentiometerValue(AnalogIn potentiometer) {
    return potentiometer.read();
}

windshieldMode_t modeSelectedUpdate() {
    float modeSelectValue = getPotentiometerValue(modeSelect); 
    if (modeSelectValue < HI_MODE_MAX) {
        return HI;
    }
    else if (modeSelectValue < LOW_MODE_MAX) {
        return LO;
    }
    else if (modeSelectValue < INT_MODE_MAX) {
        return INT;
    }
    else {
        return OF; 
    }
}

windshieldDelay_t delaySelectedUpdate() {
    float delaySelectValue = getPotentiometerValue(delaySelect); 
    if (delaySelectValue < SHORT_MODE_MAX) {
        return SHORT;
    }
    else if (delaySelectValue < MEDIUM_MODE_MAX) {
        return MEDIUM;
    }
    else {
        return LONG;
    }
}
