//=====[#include guards - begin]===============================================

#ifndef _SERVO_MOTOR_H_
#define _SERVO_MOTOR_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef enum{
    HI_D,
    LO_D,
    INT_D,
    OF_D
} motorDelay;

typedef enum{
    three,
    six,
    eight
} IntDelay;

typedef enum {
    DIRECTION_1,
    DIRECTION_2,
    STOPPED
} motorDirection_t;

//=====[Declarations (prototypes) of public functions]=========================

void motorControlInit();
void motorControl(motorDelay motorSpeed, int IntTime);

//=====[#include guards - end]=================================================

#endif // _SERVO_MOTOR_H_
