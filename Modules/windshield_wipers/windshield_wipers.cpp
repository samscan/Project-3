#include "mbed.h"
#include "arm_book_lib.h"

#include "windshield_wipers.h"

#define TIME_INCREMENT_MS           10
#define HI_MODE_MAX                 0.25
#define LOW_MODE_MAX                0.50
#define INT_MODE_MAX                0.75
#define OF_MODE_MAX                 1.00
#define SHORT_MODE_MAX              0.33
#define MEDIUM_MODE_MAX             0.67
#define LONG_MODE_MAX               1.00

AnalogIn modeSelectReading(A0);
AnalogIn delaySelectReading(A1);

windshieldMode_t modeSelectedUpdate() {
    float modeSelectValue = modeSelectReading; 
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
    float delaySelectValue = delaySelectReading; 
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
