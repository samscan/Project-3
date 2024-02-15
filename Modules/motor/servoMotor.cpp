//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "servoMotor.h"
#include "windshield_wiper_subsystem.h"


//=====[Declaration of private defines]========================================

#define DUTY_MIN 0.02
#define DUTY_MAX 0.117
#define PERIOD 0.02
#define LESS_THAN_A_SECOND 750 
#define ONE_AND_HALF_SECONDS 1500
#define THREE_SECONDS 3000
#define SIX_SECONDS 6000
#define EIGHT_SECONDS 8000

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

PwmOut servo(PF_9);


//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============


//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void motorControlInit()
{
    servo.period(PERIOD);
    servo.write(DUTY_MIN);
}

void moveSixtySevenDegrees(){
    float duty = (DUTY_MAX * 67)/(180);
    servo.write(duty);
}

void resetMotor(){
    servo.write(DUTY_MIN);
}

void motorControl(motorDelay motorSpeed, int IntTime)
{

    if(motorSpeed != INT_D && motorSpeed != OF_D){
        if (motorSpeed == HI_D) {
        moveSixtySevenDegrees();

        delay(LESS_THAN_A_SECOND);
    
        resetMotor();
        
        } else if(motorSpeed == LO_D){

        moveSixtySevenDegrees();

        delay(ONE_AND_HALF_SECONDS);
    
        resetMotor();

        }
    } else if (motorSpeed == INT_D){
        if(IntTime == 3000){

        moveSixtySevenDegrees();

        delay(THREE_SECONDS);
    
        resetMotor();

        } else if (IntTime == 6000){
        
        moveSixtySevenDegrees();

        delay(SIX_SECONDS);
    
        resetMotor();
        
        } else if (IntTime == 8000){
        
        moveSixtySevenDegrees();

        delay(EIGHT_SECONDS);
    
        resetMotor();
        }
    }


}

//=====[Implementations of private functions]==================================