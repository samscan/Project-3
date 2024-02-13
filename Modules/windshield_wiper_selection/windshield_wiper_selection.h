#ifndef _WINDSHIELD_WIPER_SELECTION_H_
#define _WINDSHIELD_WIPER_SELECTION_H_

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

windshieldMode_t modeSelectedUpdate();
windshieldDelay_t delaySelectedUpdate();

#endif 