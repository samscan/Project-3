//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "servoMotor.h"
#include "windshield_wiper_subsystem.h"

#define TIME_INCREMENT_MS 10
#define DUTY_MIN 0.020
#define DUTY_MAX 0.109
#define PERIOD 0.02
#define INTERVAL_TIME 0.04

PwmOut servo(PF_9);

int accumulatedTimeDelay = 0;
int accumulatedIntervalTime = 0;
float duty = DUTY_MIN;
int accumulatedNumOfIntervals = 0;

void motorControlInit(); 
float getSecToMoveSSD(int rpm);
int getNumIntervals(float totalTime);
float getDutyMovePerInterval(float numOfIntervals);
void motorControl(float dutyInt, float numOfIntervals);


void motorControlInit()
{
    servo.period(PERIOD);
    servo.write(DUTY_MIN);
}

float getSecToMoveSSD(int rpm){
    float mseconds = 67.0 / (rpm / 60.0 * 360.0) * 1000.0;
    return mseconds; 
}

int getNumIntervals(float totalTime) {
    float numOfIntervals = totalTime / (INTERVAL_TIME * 1000.0);
    return numOfIntervals; 
} 

float getDutyMovePerInterval(float numOfIntervals) {
    float degrees = 67.0 / numOfIntervals;
    float dutyInt = (DUTY_MAX - DUTY_MIN) / 180.0 * degrees; 
    return dutyInt;
}

void motorHiMode() {
    float oneMoveTime = getSecToMoveSSD(30);
    int numOfIntervals = getNumIntervals(oneMoveTime);
    float dutyInt = getDutyMovePerInterval(numOfIntervals);
    motorControl(dutyInt, numOfIntervals);
}

void motorLoMode() {
    float oneMoveTime = getSecToMoveSSD(20);
    int numOfIntervals = getNumIntervals(oneMoveTime);
    float dutyInt = getDutyMovePerInterval(numOfIntervals);
    motorControl(dutyInt, numOfIntervals);
}

void motorOfMode() {
    servo.write(DUTY_MIN);
}

void motorIntMode(int delayTime) {
    float oneMoveTime = getSecToMoveSSD(20);
    int numOfIntervals = getNumIntervals(oneMoveTime);
    float dutyInt = getDutyMovePerInterval(numOfIntervals);
    if (accumulatedIntervalTime == 0 && accumulatedNumOfIntervals == 0) {
        duty = DUTY_MIN;
        servo.write(duty); 
    }
    else if (accumulatedIntervalTime >= INTERVAL_TIME && accumulatedNumOfIntervals < numOfIntervals) {
        duty = duty + dutyInt;
        servo.write(duty); 
    }
    else if (accumulatedIntervalTime >= INTERVAL_TIME && accumulatedNumOfIntervals >= numOfIntervals && accumulatedNumOfIntervals < 2 * numOfIntervals) {
        duty = duty - dutyInt;
        servo.write(duty);
    }

    if (accumulatedIntervalTime >= INTERVAL_TIME) {
        accumulatedIntervalTime = 0;
        accumulatedNumOfIntervals = accumulatedNumOfIntervals + 1;
    }
    else {
        accumulatedIntervalTime = accumulatedIntervalTime + TIME_INCREMENT_MS; 
    }

    if (accumulatedTimeDelay >= delayTime) {
            accumulatedTimeDelay = 0;
            accumulatedNumOfIntervals = 0;
        }
    else {
        accumulatedTimeDelay = accumulatedTimeDelay + TIME_INCREMENT_MS; 
    }

    /*float speedDelay = getLoModeSpeed();
    if (accumulatedTimeDelay <= ) {
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
    }*/
}

void motorControl(float dutyInt, float numOfIntervals) {
    if (accumulatedIntervalTime == 0 && accumulatedNumOfIntervals == 0) {
        duty = DUTY_MIN;
        servo.write(duty); 
    }
    else if (accumulatedIntervalTime >= INTERVAL_TIME && accumulatedNumOfIntervals < numOfIntervals) {
        duty = duty + dutyInt;
        servo.write(duty); 
    }
    else if (accumulatedIntervalTime >= INTERVAL_TIME && accumulatedNumOfIntervals >= numOfIntervals && accumulatedNumOfIntervals < 2 * numOfIntervals) {
        duty = duty - dutyInt;
        servo.write(duty);
    }

    if (accumulatedIntervalTime >= INTERVAL_TIME) {
        accumulatedIntervalTime = 0;
        accumulatedNumOfIntervals = accumulatedNumOfIntervals + 1;
        if (accumulatedNumOfIntervals >= 2 * numOfIntervals) {
            accumulatedNumOfIntervals = 0;
        }
    }
    else {
        accumulatedIntervalTime = accumulatedIntervalTime + TIME_INCREMENT_MS; 
    }
}
