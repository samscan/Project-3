//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "ignition_subsystem.h"
#include "windshield_wiper_subsystem.h"
#include "display_subsystem.h"

#define TIME_INCREMENT_MS                       10

//=====[Main function, the program entry point after power on or reset]========

int main() 
{
    ignitionInit();
    windshieldWiperInit();
    displayInit();
    while (true){
        ignitionUpdate();
        windshieldWiperUpdate();
        displayUpdate();
        delay(TIME_INCREMENT_MS);
    }
}
