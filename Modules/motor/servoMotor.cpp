//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "servoMotor.h"
#include "windshield_wiper_subsystem.h"

//=====[Declaration of private defines]========================================

#define TIME_INCREMENT_MS 10
#define DUTY_MIN 0.030
#define DUTY_MAX 0.135
#define PERIOD 0.02
#define INTERVAL_TIME 0.04

//=====[Declaration and initialization of public global objects]===============

PwmOut servo(PF_9);

//=====[Declaration and initialization of public global variables]=============

int accumulatedTimeDelay = 0;
int accumulatedIntervalTime = 0;
float duty = DUTY_MIN;
int accumulatedNumOfIntervals = 0;

//=====[Declarations (prototypes) of private functions]========================

void motorControlInit(); 
float getSecToMoveSSD(int rpm);
int getNumIntervals(float totalTime);
float getDutyMovePerInterval(float numOfIntervals);
void motorControl(float dutyInt, float numOfIntervals);

//=====[Implementations of public functions]===================================

//makes the motor turns 67 degrees at a fast pace. 
void motorHiMode() {
    float oneMoveTime = getSecToMoveSSD(30);
    int numOfIntervals = getNumIntervals(oneMoveTime);
    float dutyInt = getDutyMovePerInterval(numOfIntervals);
    motorControl(dutyInt, numOfIntervals);
}

//makes the motor turn 67 degrees at a slow pace. 
void motorLoMode() {
    float oneMoveTime = getSecToMoveSSD(20);
    int numOfIntervals = getNumIntervals(oneMoveTime);
    float dutyInt = getDutyMovePerInterval(numOfIntervals);
    motorControl(dutyInt, numOfIntervals);
}

//makes the motor stay off at its initial position. 
void motorOfMode() {
    servo.write(DUTY_MIN);
}

/*makes the motor turn 67 degrees at a slow pace with the appropriate delay 
time between cycles. */
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
    else if (accumulatedIntervalTime >= INTERVAL_TIME && accumulatedNumOfIntervals > numOfIntervals && accumulatedNumOfIntervals < 2 * numOfIntervals) {
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
}

//=====[Implementations of private functions]==================================

//initializes the servo motor. 
void motorControlInit()
{
    servo.period(PERIOD);
    servo.write(DUTY_MIN);
}

//returns the time it takes to move 67 degrees at a specific rate. 
float getSecToMoveSSD(int rpm){
    float mseconds = 67.0 / (rpm / 60.0 * 134.0) * 1000.0;
    return mseconds; 
}

/* returns the number of 40 millisecond intervals it takes the motor to turn 
67 degrees. */
int getNumIntervals(float totalTime) {
    float numOfIntervals = totalTime / (INTERVAL_TIME * 1000.0);
    return numOfIntervals; 
} 

/*returns the amount of duty added to the motor every 40 milliseconds in order
to reach 67 degrees in the appropriate amount of intervals. */
float getDutyMovePerInterval(float numOfIntervals) {
    float degrees = 67.0 / numOfIntervals;
    float dutyInt = (DUTY_MAX - DUTY_MIN) / 180.0 * degrees; 
    return dutyInt;
}

/*increments the servo motor at the appropriate pace (fast or slow) determined 
by the parameters of the duty incremented every 40 milliseconds and the number 
of 40 millisecond intervals cycled through to turn to 67 degrees. */
void motorControl(float dutyInt, float numOfIntervals) {
    if (accumulatedIntervalTime == 0 && accumulatedNumOfIntervals == 0) {
        duty = DUTY_MIN;
        servo.write(duty); 
    }
    else if (accumulatedIntervalTime >= INTERVAL_TIME && accumulatedNumOfIntervals < numOfIntervals) {
        duty = duty + dutyInt;
        servo.write(duty); 
    }
    else if (accumulatedIntervalTime >= INTERVAL_TIME && accumulatedNumOfIntervals > numOfIntervals && accumulatedNumOfIntervals < 2 * numOfIntervals) {
        duty = duty - dutyInt;
        servo.write(duty);
    }

    if (accumulatedIntervalTime > INTERVAL_TIME) {
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
