#ifndef _IGNITION_BUTTON_H_
#define _IGNITION_BUTTON_H_

#define DEBOUNCE_BUTTON_TIME_MS                 40

int ignitionPressedDebounceTime = 0;

void ignitionInit();
void ignitionUpdate();
void checkStartEngine();
void checkStopEngine();

#endif 
