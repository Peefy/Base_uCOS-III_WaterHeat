#include "flash.h"
#include "TempControl.h"
#include "stm32f10x_flash.h"

#define FLASH_SAVE1	TempPara.Set	 
#define FLASH_SAVE2	1
#define FLASH_SAVE3	1
#define FLASH_SAVE4	1

u32 StartAddress = 0x0800f000;
volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;

u32 Readflash(char i)
{
	uint32_t data;
	uint32_t *p = (uint32_t*)(StartAddress+i);
	data = *p;
	return data;
}

void WriteFlash(void)
{
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR); 
    FLASHStatus = FLASH_ErasePage(StartAddress);
	if(FLASHStatus == FLASH_COMPLETE)
	{
		FLASHStatus = FLASH_ProgramWord(StartAddress, FLASH_SAVE1	);
		FLASHStatus = FLASH_ProgramWord(StartAddress+4, 0xE234567F);
		FLASHStatus = FLASH_ProgramWord(StartAddress+8, 0xE234567F);
		FLASHStatus = FLASH_ProgramWord(StartAddress+12, 0xE234567F);
	}
	
}

void ReadFlash(void)
{
  FLASH_SAVE1	= (u16)Readflash(0);

}

