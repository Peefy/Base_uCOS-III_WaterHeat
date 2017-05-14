#ifndef  __BSP_H__
#define  __BSP_H__

#include "stm32f10x.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_rcc.h"
#include "os_cfg_app.h"
#include "bsp_led.h"
#include "delay.h"

void PLL_Configuration(void);//72M
void BSP_Init(void);
void SysTick_init(void);


#endif /* __BSP_H__ */



