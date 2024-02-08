#include "mbed.h"
#include "arm_book_lib.h"

#include "ignition_subsystem.h"
#include "windshield_wiper_subsystem.h"

#define TIME_INCREMENT_MS                       10

int main() 
{
    ignitionInit();
    windshieldWiperInit();
    while (true){
        ignitionUpdate();
        windshieldWiperUpdate();
        delay(TIME_INCREMENT_MS);
    }
}
