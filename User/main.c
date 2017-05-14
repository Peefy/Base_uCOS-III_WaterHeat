/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   os ������ ����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� ISO-MINI STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "includes.h"

OS_TCB	StartUp_TCB;		   					          //����������ƿ�
CPU_STK	StartUp_Stk[STARTUP_TASK_STK_SIZE];		//���������ջ

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
  OS_ERR err;	

  /* �弶��ʼ�� */	
	BSP_Init();

  /* ��ʼ��"uC/OS-III"�ں� */  
	OSInit(&err);		                                        
  
	/*��������*/
	OSTaskCreate((OS_TCB     *)&StartUp_TCB,                // ������ƿ�ָ��          
               (CPU_CHAR   *)"StartUp",		                // ��������
               (OS_TASK_PTR )Task_Start, 	                // �������ָ��
               (void       *)0,			                      // ���ݸ�����Ĳ���parg
               (OS_PRIO     )STARTUP_TASK_PRIO,			      // �������ȼ�
               (CPU_STK    *)&StartUp_Stk[0],	            // �����ջ����ַ
               (CPU_STK_SIZE)STARTUP_TASK_STK_SIZE/10,	  // ��ջʣ�ྯ����
               (CPU_STK_SIZE)STARTUP_TASK_STK_SIZE,			  // ��ջ��С
               (OS_MSG_QTY  )0,			                      // �ɽ��յ������Ϣ������
               (OS_TICK     )0,			                      // ʱ��Ƭ��תʱ��
               (void       *)0,			                      // ������ƿ���չ��Ϣ
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	      // ����ѡ��
               (OS_ERR     *)&err);		                    // ����ֵ
	  
  /* ����������ϵͳ������Ȩ����uC/OS-II */
  OSStart(&err);                                       
}

/*********************************************END OF FILE**********************/
