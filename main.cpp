//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

//=====[Defines]===============================================================

#define TIME_INCREMENT_MS                       10
#define DEBOUNCE_BUTTON_TIME_MS                 40
#define DAYLIGHT_LEVEL                          0.888
#define DUSK_LEVEL                              0.76

//=====[Declaration of public data types]======================================

typedef enum {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_FALLING,
    BUTTON_RISING
} buttonState_t;

typedef enum {
    DAYLIGHT,
    DUSK,
    BETWEEN
} lightLevelState_t;

//=====[Declaration and initialization of public global objects]===============



//=====[Main function, the program entry point after power on or reset]========

int main() 
{
    inputsInit();
    outputsInit();
    while (true){
        engineUpdate();
        headlightUpdate();
        delay(TIME_INCREMENT_MS);
    }
}

//=====[Implementations of public functions]===================================

