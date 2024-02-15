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

void windshieldWiperInit() {
    // Initialize the servo motor for the windshield wiper
    servoMotorInit();
    // Set the initial mode of the windshield wiper to OFF
    servoMotorWrite(OF_MODE_MAX);
}

void windshieldWiperUpdate() {
    static Timer timer;
    static int elapsedTime = 0;
    
    // Start the timer if it's not already running
    if (!timer.running) {
        timer.start();
    }
    
    // Update only every TIME_INCREMENT_MS milliseconds
    if (timer.read_ms() - elapsedTime >= TIME_INCREMENT_MS) {
        elapsedTime = timer.read_ms();
        
        windshieldMode_t currentMode = modeSelectedUpdate();
        windshieldDelay_t currentDelay = delaySelectedUpdate();
        
        // Adjust the servo motor based on the current mode and delay
        switch (currentMode) {
            case HI:
                servoMotorWrite(HI_MODE_MAX);
                break;
            case LO:
                servoMotorWrite(LOW_MODE_MAX);
                break;
            case INT:
                // For intermittent mode, we use the delay to adjust the pause between wipes
                static int delayTime = 0;
                if (delayTime <= 0) {
                    servoMotorWrite(INT_MODE_MAX);
                    if (currentDelay == SHORT) {
                        delayTime = 1000; // 1 second for short
                    } else if (currentDelay == MEDIUM) {
                        delayTime = 2000; // 2 seconds for medium
                    } else {
                        delayTime = 3000; // 3 seconds for long
                    }
                } else {
                    delayTime -= TIME_INCREMENT_MS;
                }
                break;
            case OF:
                servoMotorWrite(OF_MODE_MAX);
                break;
        }
    }
}
