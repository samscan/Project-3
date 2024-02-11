#include "mbed.h"
#include "arm_book_lib.h"

#include "driver_seat.h"

DigitalIn driverSeat(D11);

void driverSeatInit()
{
    driverSeat.mode(PullDown);
}