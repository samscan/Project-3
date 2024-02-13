#ifndef _IGNITION_SUBSYSTEM_H_
#define _IGNITION_SUBSYSTEM_H_

typedef enum{ 
    NOT_RUNNING, 
    RUNNING
} engineStatus_t;

void ignitionInit();
void ignitionUpdate();
engineStatus_t engineStatusUpdate();

#endif 