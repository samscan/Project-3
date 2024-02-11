#include "mbed.h"
#include "arm_book_lib.h"

#include "ignition_subsystem.h"
#include "windshield_wipers.h"

#define TIME_INCREMENT_MS                       10

int main() 
{
    ignitionInit();
    windshieldWipersInit();
    while (true){
        ignitionUpdate();
        windshieldWipersUpdate();
        delay(TIME_INCREMENT_MS);
    }
}
