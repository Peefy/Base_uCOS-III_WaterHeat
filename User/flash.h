#ifndef _FLASH_H_
#define _FLASH_H_

#include <stm32f10x.h>
			 

	
u32 Readflash(char i);
void WriteFlash(void);
void ReadFlash(void);
void PowerOnSpeedSelect(void);

#endif
