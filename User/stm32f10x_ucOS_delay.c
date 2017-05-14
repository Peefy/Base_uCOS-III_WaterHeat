

#include "stm32f10x_ucOS_delay.h"
#include "stm32f10x_tim.h"
#include "stdbool.h"

bool isInit = true;

void uc0S_DelayInit(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 	
  TIM_TimeBaseStructure.TIM_Period = 1;                 
  TIM_TimeBaseStructure.TIM_Prescaler = 7200;       
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;   
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;  
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	isInit = true;
}


void ucOS_delay_ms(u16 ms) //ms 为10000时 精确延时1s  最大65535
{
	u16 TIMCounter = ms;
	if(isInit == false)
		while(1);
  TIM_Cmd(TIM3, ENABLE);
  TIM_SetCounter(TIM3, TIMCounter);
  while (TIMCounter>1)
  {
    TIMCounter = TIM_GetCounter(TIM3);
  }
  TIM_Cmd(TIM3, DISABLE);

}

void ucOS_delay_us(u16 ns)
{
	if(isInit == false)
		while(1);
}
