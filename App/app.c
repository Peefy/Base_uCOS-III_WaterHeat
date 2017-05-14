
#include "app.h"
#include "GPIOLIKE51.h"
#include "oled.h"
#include "stm32f10x.h"
#include "misc.h"
#include "TempControl.h"
#include "ds18b20.h"
#include "breathLED.h"
#include "keyEx.h"
#include "CString.h"
#include "iwdg.h"
#include "Sound.h"
#include "stm32f10x_ucOS_delay.h"

#define LED PBout(6)

extern	OS_TCB	StartUp_TCB;					

static  OS_TCB	LED1_TCB;		   				
static	CPU_STK	LED1_Stk[TASK_LED1_STK_SIZE];	   

static  OS_TCB	LED2_TCB;		   				
static	CPU_STK	LED2_Stk[TASK_LED2_STK_SIZE];	   	

static  OS_TCB	LED3_TCB;		   					
static	CPU_STK	LED3_Stk[TASK_LED3_STK_SIZE];	   


void Task_Start(void *p_arg)
{
	OS_ERR err;
  (void)p_arg;	

	//��������LED1	
	OSTaskCreate((OS_TCB     *)&LED1_TCB,					            // ������ƿ�ָ��          
               (CPU_CHAR   *)"LED1",						            // ��������
               (OS_TASK_PTR )Task_LED1,					            // �������ָ��
               (void       *)0,							                // ���ݸ�����Ĳ���parg
               (OS_PRIO     )TASK_LED1_PRIO,				        // �������ȼ�
               (CPU_STK    *)&LED1_Stk[0],				          // �����ջ����ַ
               (CPU_STK_SIZE)TASK_LED1_STK_SIZE/10,		      // ��ջʣ�ྯ����
               (CPU_STK_SIZE)TASK_LED1_STK_SIZE,			      // ��ջ��С
               (OS_MSG_QTY  )0,							                // �ɽ��յ������Ϣ������
               (OS_TICK     )0,							                // ʱ��Ƭ��תʱ��
               (void       *)0,							                // ������ƿ���չ��Ϣ
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	        // ����ѡ��
               (OS_ERR     *)&err);						              // ����ֵ

	//��������LED2	
	OSTaskCreate((OS_TCB     *)&LED2_TCB,					     
               (CPU_CHAR   *)"LED2",						
               (OS_TASK_PTR )Task_LED2,					
               (void       *)0,							
               (OS_PRIO     )TASK_LED2_PRIO,				
               (CPU_STK    *)&LED2_Stk[0],				
               (CPU_STK_SIZE)TASK_LED2_STK_SIZE/10,		
               (CPU_STK_SIZE)TASK_LED2_STK_SIZE,			
               (OS_MSG_QTY  )0,							
               (OS_TICK     )0,							
               (void       *)0,							
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	 
               (OS_ERR     *)&err);					

	//��������LED3	
	OSTaskCreate((OS_TCB     *)&LED3_TCB,					  
               (CPU_CHAR   *)"LED3",						
               (OS_TASK_PTR )Task_LED3,				
               (void       *)0,							
               (OS_PRIO     )TASK_LED3_PRIO,				
               (CPU_STK    *)&LED3_Stk[0],				
               (CPU_STK_SIZE)TASK_LED3_STK_SIZE/10,		
               (CPU_STK_SIZE)TASK_LED3_STK_SIZE,			
               (OS_MSG_QTY  )0,						
               (OS_TICK     )0,							
               (void       *)0,							
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	 
               (OS_ERR     *)&err);	
               
  //����ɾ���Լ�	
	OSTaskDel(&StartUp_TCB,&err);							 
}


void Task_LED1(void *p_arg)
{
  OS_ERR err;
  (void)p_arg;                	

  while (1)
  {
    BreathLedTimerDelegate();
	  KeyExTimerDelegate();  
		TaskDelay(9);
  }
}

bool isDs18b20Error = true;
void Task_LED2(void *p_arg)
{
  OS_ERR err;
  (void)p_arg;       
	
	OLED_Init();
	
  while (1)
  {
		
    LCD_P8x16Str(0,0,Str.Add("SetTemp:",Str.Float2Str(TempPara.Set / 10.0)));
		LCD_P8x16Str(0,2,Str.Add("NowTemp:",Str.Float2Str(TempPara.Now / 10.0)));
	  //LCD_P8x16Str(0,4,Str.Add("DS18B20:",Str.Bool2Str(isDs18b20Error)));
		LCD_P8x16Str(0,6,BreathLedEnable ? "Heat:On ":"Heat:Off");
		FeedDog;
		TaskDelay(10);
  }
}


void Task_LED3(void *p_arg)
{
  OS_ERR err;
  (void)p_arg;   

  while (1)
  {
	  TempControlTimerDelegate();
    TaskDelay(8);
  }
}

/* -------------------------------------end of file------------------------------------ */
