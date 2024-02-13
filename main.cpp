#include "mbed.h"
#include "arm_book_lib.h"

#include "ignition_subsystem.h"
#include "windshield_wipers.h"
#include "display.h"

#define TIME_INCREMENT_MS                       10

int main() 
{
    ignitionInit();
    displayInit();
    while (true){
        ignitionUpdate();
        displayUpdate();
        delay(TIME_INCREMENT_MS);
    }
}
