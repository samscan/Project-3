//=====[#include guards - begin]===============================================

#ifndef _SERVO_MOTOR_H_
#define _SERVO_MOTOR_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================


//=====[Declarations (prototypes) of public functions]=========================
void motorControlInit();
void motorHiMode(); 
void motorLoMode();
void motorOfMode();
void motorIntMode(int delayTime);

//=====[#include guards - end]=================================================

#endif // _SERVO_MOTOR_H_
