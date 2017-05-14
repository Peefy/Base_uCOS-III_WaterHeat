#ifndef _IWDG_H_
#define _IWDG_H_

#include "stm32f10x_iwdg.h"

#define IWDG_EN 1

void IWDG_Init(void);

#define FeedDog IWDG_ReloadCounter()		
									  
#endif
