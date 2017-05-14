
#include "keyEx.h"
#include "stm32f10x_gpio.h"
#include "TempControl.h"
#include "flash.h"

#define ARR_SIZE( a ) ( sizeof( (a) ) / sizeof( ((a)[0]) ) )

void DoKey1Event(void);
void DoKey2Event(void);
void DoKey3Event(void);

Key_t Keys[] = 
{
	{0,0,0,DoKey1Event},
	{0,0,0,DoKey2Event},
	{0,0,0,DoKey3Event}
};

void KeyExtralInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE); 				 	 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

KeyStatus_t GetKeyExtralTotalStatus(void)
{
	KeyStatus_t keyStatus;
	keyStatus.Key2PressDown = !GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
	keyStatus.Key1PressDown = !GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9);
	keyStatus.Key3PressDown = !GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10);
	return keyStatus;
}

char key1Time = 0;	
char key2Time = 0;	
char key3Time = 0;	

void KeyExTimerDelegate(void)
{
	char i = 0;
	char keyNum = ARR_SIZE(Keys);
	KeyStatus_t keyStatus = GetKeyExtralTotalStatus();
	Keys[0].PressDown = keyStatus.Key1PressDown;
	Keys[1].PressDown = keyStatus.Key2PressDown;
	Keys[2].PressDown = keyStatus.Key3PressDown;
	
	for(i = 0;i < keyNum;++i)
	{
		if(Keys[i].PressDown == true)
		{
			if( ++ Keys[i].DownTime >= 50)
				Keys[i].DownTime = 50;
		}			
		else
			Keys[i].DownTime = 0;
		if(Keys[i].DownTime == (KEYEX_DOWN_TIME + 1))
			Keys[i].Event();
		if(Keys[i].DownTime >= (KEYEX_HOLD_TIME + 1))
		{
			if(++ Keys[i].LongDownDelay >= 10)
			{
				Keys[i].Event();
				Keys[i].LongDownDelay = 0;
			}
		}			
	}
	
}

void DoKey1Event(void)
{
  TempPara.Set += 10;
	if(TempPara.Set >= 750)
		TempPara.Set = 750;

}

void DoKey2Event(void)
{
	TempPara.Set -= 10;
	if(TempPara.Set <= 80)
		TempPara.Set = 80;

}

void DoKey3Event(void)
{
	TempPara.Set -= 10;
	if(TempPara.Set <= 100)
		TempPara.Set = 100;

}
