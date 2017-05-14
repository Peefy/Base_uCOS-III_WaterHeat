
#include "Sound.h"

OS_ERR err_;

void sound_init()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PB�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = FMQ_Pin ;				 //�������˿�
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOC, &GPIO_InitStructure);
 GPIO_ResetBits(FMQ_GPIO,FMQ_Pin);	
 //kaiji_fmq()	;
}

/************************************************************************
* ��  ��  ��  : delay_fmq
* ��      ��  :��������ʱ����
* ��      ��  : ��.
* ��      ��  : ��.
************************************************************************/


/************************************************************************
* ��  ��  ��  : kaiji_fmq
* ��      ��  : ������ʾ��
* ��      ��  : ��.
* ��      ��  : ��.
************************************************************************/
void kaiji_fmq()			 //������
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
* ��  ��  ��  : up_fmq
* ��      ��  : 5�򰴼����ϼ�
* ��      ��  : ��.
* ��      ��  : ��.
************************************************************************/
void up_fmq()			 //���ϼ���
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
* ��  ��  ��  : down_fmq
* ��      ��  : 5�򰴼����¼��򰴼�������
* ��      ��  : ��.
* ��      ��  : ��.
************************************************************************/
void down_fmq()			 //���¼���
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
* ��  ��  ��  : left_fmq
* ��      ��  : 5�򰴼������
* ��      ��  : ��.
* ��      ��  : ��.
************************************************************************/
void left_fmq()			 //�������
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
* ��  ��  ��  : right_fmq
* ��      ��  : 5�򰴼����Ҽ�
* ��      ��  : ��.
* ��      ��  : ��.
************************************************************************/
void right_fmq()			 //���Ҽ���
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
* ��  ��  ��  : ok_fmq
* ��      ��  : 5�򰴼�OK��
* ��      ��  : ��.
* ��      ��  : ��.
************************************************************************/
void ok_fmq()			  //ok����
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
* ��  ��  ��  : ok_fmq
* ��      ��  : 5�򰴼�OK�������򳤰���
* ��      ��  : ��.
* ��      ��  : ��.
************************************************************************/
void ok_hold_fmq()			  //ok��������
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
