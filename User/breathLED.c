
#include "breathLED.h"
#include "pwm.h"
#include "delay.h"
#include "stm32f10x_tim.h"

bool BreathLedEnable = false;

void BreathLedInit(void)
{
	TIM4_PWM_Init();
}

int ledFx = 0;
int ledDt = 0;

void BreathLedTimerDelegate(void)
{
  if(BreathLedEnable == true)
	{
	  if(ledFx == 1)
		  ledDt ++;
	  else
		  ledDt --;
	  if(ledDt > 140) ledFx = 0;
	  if(ledDt <= 0) ledFx = 1;
	  TIM_SetCompare1(TIM4,ledDt);		
	}
	else
	{
		TIM_SetCompare1(TIM4,139);	
	}

}


