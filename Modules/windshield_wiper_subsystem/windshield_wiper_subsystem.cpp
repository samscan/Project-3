//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "windshield_wiper_subsystem.h"
#include "servoMotor.h"
#include "ignition_subsystem.h"

//=====[Declaration of private defines]========================================

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

//=====[Declaration and initialization of public global objects]===============

AnalogIn modeSelect(A0);
AnalogIn delaySelect(A1);

//=====[Declaration and initialization of public global variables]=============

int accumulatedTime = 0;
int delayTime = 0; 

//=====[Declarations (prototypes) of private functions]========================

float getPotentiometerValue(AnalogIn potentiometer);

//=====[Implementations of public functions]===================================

//returns the current mode selected by the appropriate potentiometer. 
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

//returns the current delay selected by the appropriate potentiometer. 
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

//initializes the windshield wipers system 
void windshieldWiperInit() {
    motorControlInit();
}

/* updates the windshield wipers so they execute the appropriate mode and 
delay selected. */ 
void windshieldWiperUpdate() {
    engineStatus_t engineStatus = engineStatusUpdate();
    if (engineStatus == RUNNING) {
        windshieldMode_t currentMode = modeSelectedUpdate();
        windshieldDelay_t currentDelay = delaySelectedUpdate();
        
        // adjust the servo motor based on the current mode and delay
        switch (currentMode) {
            case HI:
                motorHiMode();
                break;
            case LO:
                motorLoMode();
                break;
            case INT:
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

//=====[Implementations of private functions]==================================

//returns the value read from the potentiometer. 
float getPotentiometerValue(AnalogIn potentiometer) {
    return potentiometer.read();
}