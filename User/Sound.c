
#include "Sound.h"

OS_ERR err_;

void sound_init()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PB端口时钟
	
 GPIO_InitStructure.GPIO_Pin = FMQ_Pin ;				 //蜂鸣器端口
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOC, &GPIO_InitStructure);
 GPIO_ResetBits(FMQ_GPIO,FMQ_Pin);	
 //kaiji_fmq()	;
}

/************************************************************************
* 函  数  名  : delay_fmq
* 描      述  :蜂鸣器延时函数
* 输      入  : 无.
* 返      回  : 无.
************************************************************************/


/************************************************************************
* 函  数  名  : kaiji_fmq
* 描      述  : 开机提示音
* 输      入  : 无.
* 返      回  : 无.
************************************************************************/
void kaiji_fmq()			 //开机音
{
	u8 a;
	for(a=100;a>0;a--)
	 {
		buzzer = !buzzer;
		delay_fmq(20);
	 }
	for(a=100;a>0;a--)
	 {
		buzzer = !buzzer;
		delay_fmq(15);
	 }
	for(a=100;a>0;a--)
	 {
		buzzer = !buzzer;
		delay_fmq(10);
	 }
	 for(a=100;a>0;a--)
	 {
		buzzer = !buzzer;
		delay_fmq(5);
	 }
	GPIO_ResetBits( FMQ_GPIO, FMQ_Pin);
}

/************************************************************************
* 函  数  名  : up_fmq
* 描      述  : 5向按键向上键
* 输      入  : 无.
* 返      回  : 无.
************************************************************************/
void up_fmq()			 //向上键音
{
	u8 a;
	for(a=100;a>0;a--)
	 {
		buzzer = !buzzer;
		delay_fmq(6);
	 }
	for(a=100;a>0;a--)
	 {
		buzzer = !buzzer;
		delay_fmq(12);
	 }
	for(a=100;a>0;a--)
	 {
		buzzer = !buzzer;
		delay_fmq(6);
	 } 
	GPIO_ResetBits( FMQ_GPIO, FMQ_Pin);
}


/************************************************************************
* 函  数  名  : down_fmq
* 描      述  : 5向按键向下键或按键按下音
* 输      入  : 无.
* 返      回  : 无.
************************************************************************/
void down_fmq()			 //向下键音
{
	u8 a;
	for(a=100;a>0;a--)
	 {
		buzzer = !buzzer;
		delay_fmq(20);
	 }
	for(a=100;a>0;a--)
	 {
		buzzer = !buzzer;
		delay_fmq(6);
	 }
	for(a=100;a>0;a--)
	 {
		buzzer = !buzzer;
		delay_fmq(15);
	 }
	GPIO_ResetBits( FMQ_GPIO,  FMQ_Pin);
}

/************************************************************************
* 函  数  名  : left_fmq
* 描      述  : 5向按键向左键
* 输      入  : 无.
* 返      回  : 无.
************************************************************************/
void left_fmq()			 //向左键音
{
	u8 a;
	for(a=50;a>0;a--)
	 {
		buzzer = !buzzer;
		delay_fmq(5);
	 }
	for(a=50;a>0;a--)
	 {
		buzzer = !buzzer;
		delay_fmq(10);
	 }
	for(a=50;a>0;a--)
	 {
		buzzer = !buzzer;
		delay_fmq(15);
	 } 
	GPIO_ResetBits(FMQ_GPIO, FMQ_Pin);
}

/************************************************************************
* 函  数  名  : right_fmq
* 描      述  : 5向按键向右键
* 输      入  : 无.
* 返      回  : 无.
************************************************************************/
void right_fmq()			 //向右键音
{
	u8 a;
	for(a=50;a>0;a--)
	 {
		buzzer = !buzzer;
		delay_fmq(15);
	 }
	for(a=50;a>0;a--)
	 {
		buzzer = !buzzer;
		delay_fmq(10);
	 }
	for(a=50;a>0;a--)
	 {
		buzzer = !buzzer;
		delay_fmq(5);
	 } 
	GPIO_ResetBits( FMQ_GPIO, FMQ_Pin);
}

/************************************************************************
* 函  数  名  : ok_fmq
* 描      述  : 5向按键OK键
* 输      入  : 无.
* 返      回  : 无.
************************************************************************/
void ok_fmq()			  //ok键音
{
	u8 a;
	for(a=100;a>0;a--)
	 {
		buzzer = !buzzer;
		delay_fmq(20);
	 }
	for(a=80;a>0;a--)
	 {
		buzzer = !buzzer;
		delay_fmq(30);
	 }

	GPIO_ResetBits(FMQ_GPIO,  FMQ_Pin);
}

/************************************************************************
* 函  数  名  : ok_fmq
* 描      述  : 5向按键OK长按键或长按键
* 输      入  : 无.
* 返      回  : 无.
************************************************************************/
void ok_hold_fmq()			  //ok键长按音
{
	u16 a;
	for(a=200;a>0;a--)
	 {
		buzzer = !buzzer;
		delay_fmq(10);
	 }
	GPIO_ResetBits(FMQ_GPIO,  FMQ_Pin);
	delay_fmq(20);
	for(a=200;a>0;a--)
	 {
		buzzer = !buzzer;
		delay_fmq(10);
	 }
	GPIO_ResetBits( FMQ_GPIO,  FMQ_Pin);
	delay_fmq(20);
	for(a=200;a>0;a--)
	 {
		buzzer = !buzzer;
		delay_fmq(10);
	 }
	GPIO_ResetBits( FMQ_GPIO,  FMQ_Pin);
	 
}	
//*****************************END********************************** 
