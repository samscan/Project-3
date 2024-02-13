//=====[#include guards - begin]===============================================

#ifndef _SERVO_MOTOR_H_
#define _SERVO_MOTOR_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef enum {
    DIRECTION_1,
    DIRECTION_2,
    STOPPED
} motorDirection_t;

//=====[Declarations (prototypes) of public functions]=========================

void motorInitialize();
void motorInt();
void motorHi();
void motorLo();
void motorHi();

//=====[#include guards - end]=================================================

#endif // _SERVO_MOTOR_H_
