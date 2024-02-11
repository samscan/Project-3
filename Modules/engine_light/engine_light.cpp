#include "mbed.h"
#include "arm_book_lib.h"

#include "engine_light.h"



void engineInit()
{
    engine = OFF;
}

void engineUpdate() {
    if(!engine) {
        checkStartEngine();
    }
    else {
        checkStopEngine();
    }
    ignitionPressedDebounceTime = ignitionPressedDebounceTime + TIME_INCREMENT_MS;
}