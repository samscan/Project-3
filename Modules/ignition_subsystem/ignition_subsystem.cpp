//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "ignition_subsystem.h"

//=====[Declaration of private defines]========================================

#define TIME_INCREMENT_MS                       10
#define DEBOUNCE_BUTTON_TIME_MS                 40

//=====[Declaration of private data types]=====================================

typedef enum {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_FALLING,
    BUTTON_RISING
} buttonState_t;

//=====[Declaration and initialization of public global objects]===============

DigitalIn driverSeat(D11);
DigitalIn ignition(D12);

DigitalOut engine(LED2);

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

//=====[Declaration and initialization of public global variables]=============

buttonState_t ignitionButtonState;

int accumulatedDebounceButtonTime = 0;
int ignitionPressedDebounceTime = 0;

//=====[Declarations (prototypes) of private functions]========================

void checkStartEngine();
void checkStopEngine();
void debounceButtonInit();
bool debounceButtonUpdate();

//=====[Implementations of public functions]===================================

//initialize the driver seat and the ignition button with a pulldown resistor. 
void ignitionInit()
{
    driverSeat.mode(PullDown);
    ignition.mode(PullDown);
    debounceButtonInit();
}

//returns the status of the engine (either RUNNING or NOT_RUNNING).
engineStatus_t engineStatusUpdate() {
    if (engine == ON) {
        return RUNNING;
    }
    else {
        return NOT_RUNNING;
    }
}

//checks to see if the engine should be turned on or turned off. 
void ignitionUpdate() {
    if(!engine) {
        checkStartEngine();
    }
    else {
        checkStopEngine();
    }
    ignitionPressedDebounceTime = ignitionPressedDebounceTime + TIME_INCREMENT_MS;
}

//=====[Implementations of private functions]==================================

/*turns the engine on if the driver seat is being pressed, the ignition button 
is released, and the engine is already off.  */
void checkStartEngine(){
    bool ignitionButtonReleasedEvent = debounceButtonUpdate();
    if(driverSeat && ignitionButtonReleasedEvent && ignitionPressedDebounceTime >= DEBOUNCE_BUTTON_TIME_MS){

        engine = ON;
        ignitionPressedDebounceTime = 0;
    }
    
}

//turns the engine off if the ignition button is pressed and the engine is already on. 
void checkStopEngine(){
    bool ignitionButtonReleasedEvent = debounceButtonUpdate();
    if(ignitionButtonReleasedEvent && ignitionPressedDebounceTime >= DEBOUNCE_BUTTON_TIME_MS){
        engine = OFF;
        ignitionPressedDebounceTime = 0;
    }
}

/*debounces the ignition button and returns whether the ignition button has 
been properly released. */
bool debounceButtonUpdate()
{
    bool ignitionReleasedEvent = false;
    switch( ignitionButtonState ) {
    
    case BUTTON_UP:
        if( ignition == 1 ) {
            ignitionButtonState = BUTTON_FALLING;
            accumulatedDebounceButtonTime = 0;
        }
        break;

    case BUTTON_FALLING:
        if( accumulatedDebounceButtonTime >= DEBOUNCE_BUTTON_TIME_MS ) {
            if( ignition == 1 ) {
                ignitionButtonState = BUTTON_DOWN;
            } else {
                ignitionButtonState = BUTTON_UP;
            }
        }
        accumulatedDebounceButtonTime = accumulatedDebounceButtonTime +
                                        TIME_INCREMENT_MS;
        break;

    case BUTTON_DOWN:
        if( ignition == 0 ) {
            ignitionButtonState = BUTTON_RISING;
            accumulatedDebounceButtonTime = 0;
        }
        break;

    case BUTTON_RISING:
        if( accumulatedDebounceButtonTime >= DEBOUNCE_BUTTON_TIME_MS ) {
            if( ignition == 0 ) {
                ignitionButtonState = BUTTON_UP;
                ignitionReleasedEvent = true;
                uartUsb.write( "yes\r\n", 5);
            } else {
                ignitionButtonState = BUTTON_DOWN;
            }
        }
        accumulatedDebounceButtonTime = accumulatedDebounceButtonTime +
                                        TIME_INCREMENT_MS;
        break;

    default:
        debounceButtonInit();
        break;
    }
    return ignitionReleasedEvent;
}

//determines the initial state for the debounced ignition button. 
void debounceButtonInit()
{
    if( ignition == 1) {
        ignitionButtonState = BUTTON_UP;
    } else {
        ignitionButtonState = BUTTON_DOWN;
    }
}
