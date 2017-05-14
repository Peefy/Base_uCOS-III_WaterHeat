
#ifndef _BREATHLED_H_
#define _BREATHLED_H_

#include <stm32f10x.h>
#include <stdbool.h>
#include "GPIOLIKE51.h"

extern bool BreathLedEnable;

void BreathLedInit(void);
void BreathLedTimerDelegate(void); 

#endif

