#include "mbed.h"
#include "arm_book_lib.h"

#include "ignition_button.h"

DigitalIn ignition(D12);

typedef enum {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_FALLING,
    BUTTON_RISING
} buttonState_t;

buttonState_t ignitionButtonState;
int accumulatedDebounceButtonTime = 0;

void debounceButtonInit();
bool debounceButtonUpdate();

void ignitionInit()
{
    ignition.mode(PullDown);
}

void checkStartEngine(){
    bool ignitionButtonReleasedEvent = debounceButtonUpdate();
    if(driverSeat && ignitionButtonReleasedEvent && ignitionPressedDebounceTime >= DEBOUNCE_BUTTON_TIME_MS){

        engine = ON;
        ignitionPressedDebounceTime = 0;
    }
    
}

void checkStopEngine(){
    bool ignitionButtonReleasedEvent = debounceButtonUpdate();
    if(ignitionButtonReleasedEvent && ignitionPressedDebounceTime >= DEBOUNCE_BUTTON_TIME_MS){
        engine = OFF;
        ignitionPressedDebounceTime = 0;
    }
}

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

void debounceButtonInit()
{
    if( ignition == 1) {
        ignitionButtonState = BUTTON_UP;
    } else {
        ignitionButtonState = BUTTON_DOWN;
    }
}
