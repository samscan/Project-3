//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "servoMotor.h"
#include "windshield_wiper_subsystem.h"

#define TIME_INCREMENT_MS 10
#define DUTY_MIN 0.020
#define DUTY_MAX 0.109
#define PERIOD 0.02

PwmOut servo(PF_9);

int accumulatedSpeedDelay = 0;
int accumulatedTimeDelay = 0;

float getHiModeSpeed();
float getLoModeSpeed();
void motorControl(int speedDelay);

void motorControlInit()
{
    servo.period(PERIOD);
    servo.write(DUTY_MIN);
}

float getHiModeSpeed() {
    float hiSpeed = 67.0 / (20.0 / 60.0 * 360.0) * 1000;
    return hiSpeed;
}

float getLoModeSpeed() {
    float loSpeed = 67.0 / (10.0 / 60.0 * 360.0) * 1000;
    return loSpeed; 
}

void motorHiMode() {
    float speedDelay = getHiModeSpeed();
    motorControl(speedDelay);
}

void motorLoMode() {
    float speedDelay = getLoModeSpeed();
    motorControl(speedDelay);
}

void motorOfMode() {
    servo.write(DUTY_MIN);
}

void motorIntMode(int delayTime) {
    float speedDelay = getLoModeSpeed();
    if (accumulatedSpeedDelay == 0 && accumulatedTimeDelay == 0) {
        servo.write(DUTY_MAX);
    }

    if (accumulatedSpeedDelay >= speedDelay / 2 && accumulatedSpeedDelay < speedDelay) {
        servo.write(DUTY_MIN); 
    }

    if (accumulatedSpeedDelay >= speedDelay && accumulatedTimeDelay < delayTime) {
        servo.write(DUTY_MIN);
    }
    
    if (accumulatedSpeedDelay >= speedDelay && accumulatedTimeDelay >= delayTime) {
        accumulatedSpeedDelay = 0;
        accumulatedTimeDelay = 0;
    }
    else {
        accumulatedSpeedDelay = accumulatedSpeedDelay + TIME_INCREMENT_MS;
        accumulatedTimeDelay = accumulatedTimeDelay + TIME_INCREMENT_MS;
    }
}

void motorControl(int speedDelay) {
    if (accumulatedSpeedDelay == 0) {
        servo.write(DUTY_MAX);
    }

    if (accumulatedSpeedDelay >= speedDelay / 2 && accumulatedSpeedDelay < speedDelay) {
        servo.write(DUTY_MIN); 
    }

    if (accumulatedSpeedDelay >= speedDelay) {
        accumulatedSpeedDelay = 0;
    }
    else {
        accumulatedSpeedDelay = accumulatedSpeedDelay + TIME_INCREMENT_MS;
    }
}