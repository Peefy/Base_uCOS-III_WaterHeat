
#include "relay.h"
#include "stm32f10x_gpio.h"

void RelayGpioInit(void)
{
	   GPIO_InitTypeDef GPIO_InitStructure;

	/* 设置TIM1CLK 为 72MHZ */
  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
  /*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 |GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	RELAY = 1;
	
	RELAY1_OFF;
	RELAY2_OFF;
	
}

