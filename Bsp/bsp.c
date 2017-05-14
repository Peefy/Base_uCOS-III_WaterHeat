#include "bsp.h"
#include "relay.h"
#include "breathLED.h"
#include "keyEx.h"
#include "ds18b20.h"
#include "flash.h"
#include "iwdg.h"
#include "Sound.h"
#include "stm32f10x_ucOS_delay.h"
/*
 * 函数名：BSP_Init
 * 描述  ：时钟初始化、硬件初始化
 * 输入  ：无
 * 输出  ：无
 */
extern bool isDs18b20Error;
void BSP_Init(void)
{
	PLL_Configuration();
	LED_GPIO_Config();  
	delay_init();
	ReadFlash();
	BreathLedInit();
	RelayGpioInit();
	KeyExtralInit();
	//uc0S_DelayInit();
	while(DS18B20_Init())
	{
	   isDs18b20Error = true;
	}
	isDs18b20Error = false;
	sound_init();
	IWDG_Init();
  SysTick_init();
  
}

/*
 * 函数名：SysTick_init
 * 描述  ：配置SysTick定时器
 * 输入  ：无
 * 输出  ：无
 */
void SysTick_init(void)
{
  /* 初始化并使能SysTick定时器 */
  SysTick_Config(SystemCoreClock/OS_CFG_TICK_RATE_HZ);
  
  /*  配置1ms 中断一次，即os的频率为1000hz */
	if (SysTick_Config(SystemCoreClock/OS_CFG_TICK_RATE_HZ))	
	{ 
		/* Capture error */ 
		while (1);
	}
}

#define RCC_PLLSource_PREDIV1            ((uint32_t)0x00010000)
void PLL_Configuration(void)//72MHZ
{
	ErrorStatus HSEStartUpStatus;  
	RCC_DeInit();  
	RCC_HSEConfig(RCC_HSE_ON);  
	HSEStartUpStatus = RCC_WaitForHSEStartUp();  
    
	if(HSEStartUpStatus == SUCCESS)
	{
		RCC_HCLKConfig(RCC_SYSCLK_Div1);  
		RCC_PCLK2Config(RCC_HCLK_Div1);  
		RCC_PCLK1Config(RCC_HCLK_Div2);  
		FLASH_SetLatency(FLASH_Latency_2);  
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);  
		
		RCC_PLLConfig(RCC_PLLSource_PREDIV1,RCC_PLLMul_9);  
		RCC_PLLCmd(ENABLE);				      
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET); 
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); 
		while(RCC_GetSYSCLKSource() != 0x08);  
	}
}

/* --------------------------------------end of file--------------------------------------- */
