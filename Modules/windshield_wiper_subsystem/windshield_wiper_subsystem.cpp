#include "mbed.h"
#include "arm_book_lib.h"

#include "windshield_wiper_subsystem.h"
#include "servoMotor.h"
#include "ignition_subsystem.h"

#define TIME_INCREMENT_MS           10
#define HI_MODE_MAX                 0.25
#define LOW_MODE_MAX                0.50
#define INT_MODE_MAX                0.75
#define OF_MODE_MAX                 1.00
#define SHORT_MODE_MAX              0.33
#define MEDIUM_MODE_MAX             0.67
#define LONG_MODE_MAX               1.00
#define SHORT_DELAY                 3000
#define MEDIUM_DELAY                6000
#define LONG_DELAY                  8000

AnalogIn modeSelect(A0);
AnalogIn delaySelect(A1);

int accumulatedTime = 0;
int delayTime = 0; 

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

void windshieldWiperInit() {
    // Initialize the servo motor for the windshield wiper
    motorControlInit();
    // Set the initial mode of the windshield wiper to OFF
    //servoMotorWrite(OF_MODE_MAX);
}

void windshieldWiperUpdate() {
    engineStatus_t engineStatus = engineStatusUpdate();
    if (engineStatus == RUNNING) {
        windshieldMode_t currentMode = modeSelectedUpdate();
        windshieldDelay_t currentDelay = delaySelectedUpdate();
        
        // Adjust the servo motor based on the current mode and delay
        switch (currentMode) {
            case HI:
                motorHiMode();
                //servoMotorWrite(HI_MODE_MAX);
                break;
            case LO:
                motorLoMode();
                //servoMotorWrite(LOW_MODE_MAX);
                break;
            case INT:
                // For intermittent mode, we use the delay to adjust the pause between wipes
                if (currentDelay == SHORT) {
                    delayTime = SHORT_DELAY; 
                }
                else if (currentDelay == MEDIUM) {
                    delayTime = MEDIUM_DELAY;
                }
                else if (currentDelay == LONG) {
                    delayTime = LONG_DELAY;
                }
                motorIntMode(delayTime);
                break;
            case OF:
                motorOfMode();
                break;
        }
    accumulatedTime = accumulatedTime + TIME_INCREMENT_MS;
    }
}
