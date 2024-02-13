//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "servoMotor.h"
#include "windshield_wipers_subsystem.h"


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

typedef enum{
    HI,
    LO,
    INT,
    OF
} motorDelay;

typedef enum{
    three,
    six,
    eight
} IntDelay;

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

void motorControl(motorDelay motorSpeed, IntDelay IntTime)
{

    if(motorSpeed != INT && motorSpeed != OF){
        if (motorSpeed == HI) {
        moveSixtySevenDegrees();

        delay(LESS_THAN_A_SECOND);
    
        resetMotor();
        
        } else if(motorSpeed == LO){

        moveSixtySevenDegrees();

        delay(ONE_AND_HALF_SECONDS);
    
        resetMotor();

        }
    } else if (motorSpeed == INT){
        if(IntTime == three){

        moveSixtySevenDegrees();

        delay(THREE_SECONDS);
    
        resetMotor();

        } else if (IntTime == six){
        
        moveSixtySevenDegrees();

        delay(SIX_SECONDS);
    
        resetMotor();
        
        } else if (IntTime == eight){
        
        moveSixtySevenDegrees();

        delay(EIGHT_SECONDS);
    
        resetMotor();
        }
    }


}

//=====[Implementations of private functions]==================================