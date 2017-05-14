
#ifndef __BUZZER_H
#define __BUZZER_H	 

#include "GPIOLIKE51.h"
#include "stm32f10x_gpio.h"
#include "app.h"
#include "delay.h"

#define FMQ_Pin GPIO_Pin_14
#define FMQ_GPIO GPIOC

#define buzzer PCout(14)

#define delay_fmq(ms) delay_ms(ms)
void sound_init(void);
void kaiji_fmq(void);
void key_fmq(void);
void up_fmq(void);
void down_fmq(void);
void left_fmq(void);
void right_fmq(void);
void ok_fmq(void);
void ok_hold_fmq(void);


#endif
//*****************************END**********************************
