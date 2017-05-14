#ifndef	_APP_H_
#define	_APP_H_

#include "bsp.h" 
#include "os.h"  		
#include "os_type.h"

/*******************�����������ȼ�*******************/
#define STARTUP_TASK_PRIO       3
#define	TASK_LED1_PRIO			    4	   
#define	TASK_LED2_PRIO			    5
#define	TASK_LED3_PRIO			    6 

/************����ջ��С����λΪ OS_STK ��************/
#define STARTUP_TASK_STK_SIZE   80 
#define	TASK_LED1_STK_SIZE		  80  
#define	TASK_LED2_STK_SIZE		  80
#define	TASK_LED3_STK_SIZE		  80

#define TaskDelay(ms) OSTimeDlyHMSM(0,0,0,ms,OS_OPT_TIME_HMSM_STRICT,&err)

/**************** �û��������� *******************/
void Task_Start(void *p_arg);
void Task_LED1(void *p_arg);
void Task_LED2(void *p_arg);
void Task_LED3(void *p_arg);

#endif	//_APP_H_
