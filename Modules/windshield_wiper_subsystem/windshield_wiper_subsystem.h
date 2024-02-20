//=====[#include guards - begin]===============================================

#ifndef _WINDSHIELD_WIPER_SUBSYSTEM_H_
#define _WINDSHIELD_WIPER_SUBSYSTEM_H_

//=====[Declaration of public data types]======================================

typedef enum {
	HI,
	LO,
	INT,
	OF
} windshieldMode_t;

typedef enum {
	SHORT,
	MEDIUM,
	LONG
} windshieldDelay_t;

//=====[Declarations (prototypes) of public functions]=========================

void windshieldWiperInit();
void windshieldWiperUpdate();
windshieldMode_t modeSelectedUpdate();
windshieldDelay_t delaySelectedUpdate();

//=====[#include guards - end]=================================================

#endif 