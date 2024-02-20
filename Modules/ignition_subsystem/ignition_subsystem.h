//=====[#include guards - begin]===============================================

#ifndef _IGNITION_SUBSYSTEM_H_
#define _IGNITION_SUBSYSTEM_H_

//=====[Declaration of public data types]======================================

typedef enum{ 
    NOT_RUNNING, 
    RUNNING
} engineStatus_t;

//=====[Declarations (prototypes) of public functions]=========================

void ignitionInit();
void ignitionUpdate();
engineStatus_t engineStatusUpdate();

//=====[#include guards - end]=================================================

#endif 