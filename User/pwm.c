#include "pwm.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "misc.h"

static void TIM3_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

	/* ÉèÖÃTIM3CLK Îª 72MHZ */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 

  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE); 

  /*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // ¸´ÓÃÍÆÍìÊä³ö
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOA,GPIO_Pin_6);
	
  /*GPIOB Configuration: TIM3 channel 3 and 4 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
  * @brief  ÅäÖÃTIM3Êä³öµÄPWMĞÅºÅµÄÄ£Ê½£¬ÈçÖÜÆÚ¡¢¼«ĞÔ¡¢Õ¼¿Õ±È
  * @param  ÎŞ
  * @retval ÎŞ
  */
/*
 * TIMxCLK/CK_PSC --> TIMxCNT --> TIMx_ARR --> TIMxCNT ÖØĞÂ¼ÆÊı
 *                    TIMx_CCR(µçÆ½·¢Éú±ä»¯)
 * ĞÅºÅÖÜÆÚ=(TIMx_ARR +1 ) * Ê±ÖÓÖÜÆÚ
 * Õ¼¿Õ±È=TIMx_CCR/(TIMx_ARR +1)
 */
static void TIM3_Mode_Config(void)   //1k a8
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* PWMĞÅºÅµçÆ½Ìø±äÖµ */
 	u16 CCR1_Val = 0;        
// 	u16 CCR2_Val = 375;
// 	u16 CCR3_Val = 250;
// 	u16 CCR4_Val = 125;

/* ----------------------------------------------------------------------- 
    TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR+1)* 100% = 50%
    TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR+1)* 100% = 37.5%
    TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR+1)* 100% = 25%
    TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR+1)* 100% = 12.5%
  ----------------------------------------------------------------------- */

  /* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = 1000 - 1 ;       //µ±¶¨Ê±Æ÷´Ó0¼ÆÊıµ½999£¬¼´Îª1000´Î£¬ÎªÒ»¸ö¶¨Ê±ÖÜÆÚ
  TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1 ;	    //ÉèÖÃÔ¤·ÖÆµ£º9·ÖÆµ£¬¼´Îª8MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//ÉèÖÃÊ±ÖÓ·ÖÆµÏµÊı£º²»·ÖÆµ(ÕâÀïÓÃ²»µ½)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //ÏòÉÏ¼ÆÊıÄ£Ê½
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //ÅäÖÃÎªPWMÄ£Ê½1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //ÉèÖÃÌø±äÖµ£¬µ±¼ÆÊıÆ÷¼ÆÊıµ½Õâ¸öÖµÊ±£¬µçÆ½·¢ÉúÌø±ä
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //µ±¶¨Ê±Æ÷¼ÆÊıÖµĞ¡ÓÚCCR1_ValÊ±Îª¸ßµçÆ½
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);	 //Ê¹ÄÜÍ¨µÀ1
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
/*  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //ÉèÖÃÍ¨µÀ2µÄµçÆ½Ìø±äÖµ£¬Êä³öÁíÍâÒ»¸öÕ¼¿Õ±ÈµÄPWM
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);	  //Ê¹ÄÜÍ¨µÀ2
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
*/
  /* PWM1 Mode configuration: Channel3 */
/*  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;	//ÉèÖÃÍ¨µÀ3µÄµçÆ½Ìø±äÖµ£¬Êä³öÁíÍâÒ»¸öÕ¼¿Õ±ÈµÄPWM
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);	 //Ê¹ÄÜÍ¨µÀ3
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
*/
  /* PWM1 Mode configuration: Channel4 */
/*  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	//ÉèÖÃÍ¨µÀ4µÄµçÆ½Ìø±äÖµ£¬Êä³öÁíÍâÒ»¸öÕ¼¿Õ±ÈµÄPWM
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);	//Ê¹ÄÜÍ¨µÀ4
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM3, ENABLE);			 // Ê¹ÄÜTIM3ÖØÔØ¼Ä´æÆ÷ARR
*/
  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);                   //Ê¹ÄÜ¶¨Ê±Æ÷3	
}

/**
  * @brief  TIM3 Êä³öPWMĞÅºÅ³õÊ¼»¯£¬Ö»Òªµ÷ÓÃÕâ¸öº¯Êı
  *         TIM3µÄËÄ¸öÍ¨µÀ¾Í»áÓĞPWMĞÅºÅÊä³ö
  * @param  ÎŞ
  * @retval ÎŞ
  */
void TIM3_PWM_Init(void)
{
	TIM3_GPIO_Config();
	TIM3_Mode_Config();	
}


/*********************************************END OF TIM3 PWM**********************/

static void TIM4_GPIO_Config(void)  //B6
{
   GPIO_InitTypeDef GPIO_InitStructure;

	/* ÉèÖÃTIM1CLK Îª 72MHZ */
  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 
  /*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // ¸´ÓÃÍÆÍìÊä³ö
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

}

static void TIM4_Mode_Config(void)	
{
	u16 CCR1_Val = 50; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	/* PWMĞÅºÅµçÆ½Ìø±äÖµ */
       


/* ----------------------------------------------------------------------- 
    TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR+1)* 100% = 50%
    TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR+1)* 100% = 37.5%
    TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR+1)* 100% = 25%
    TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR+1)* 100% = 12.5%
  ----------------------------------------------------------------------- */

  /* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = 140;       //µ±¶¨Ê±Æ÷´Ó0¼ÆÊıµ½1999£¬¼´Îª2000´Î£¬ÎªÒ»¸ö¶¨Ê±ÖÜÆÚ
  TIM_TimeBaseStructure.TIM_Prescaler = 0 ;	    //¼´Îª1MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//ÉèÖÃÊ±ÖÓ·ÖÆµÏµÊı£º²»·ÖÆµ(ÕâÀïÓÃ²»µ½)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //ÏòÉÏ¼ÆÊıÄ£Ê½
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM4,TIM_IT_Update, DISABLE );
	
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQÍ¨µÀÊ¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);	//¸ù¾
	
  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //ÅäÖÃÎªPWMÄ£Ê½1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = 111;	   //ÉèÖÃÌø±äÖµ£¬µ±¼ÆÊıÆ÷¼ÆÊıµ½Õâ¸öÖµÊ±£¬µçÆ½·¢ÉúÌø±ä
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //µ±¶¨Ê±Æ÷¼ÆÊıÖµĞ¡ÓÚCCR1_ValÊ±Îª¸ßµçÆ½
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);	 //Ê¹ÄÜÍ¨µÀ1
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

  /* TIM4 enable counter */
  TIM_Cmd(TIM4, ENABLE);                   //
}

void TIM4_PWM_Init(void)
{
  TIM4_GPIO_Config();
	TIM4_Mode_Config();	
}

static void TIM1_GPIO_Config(void)  //B6
{
   GPIO_InitTypeDef GPIO_InitStructure;

	/* ÉèÖÃTIM1CLK Îª 72MHZ */
  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
  /*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_9|GPIO_Pin_10 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // ¸´ÓÃÍÆÍìÊä³ö
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

}

static void TIM1_Mode_Config(void)	
{
	u16 CCR1_Val = (pwmHz+1) /2; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	/* PWMĞÅºÅµçÆ½Ìø±äÖµ */
       


/* ----------------------------------------------------------------------- 
    TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR+1)* 100% = 50%
    TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR+1)* 100% = 37.5%
    TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR+1)* 100% = 25%
    TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR+1)* 100% = 12.5%
  ----------------------------------------------------------------------- */

  /* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = pwmHz;       //µ±¶¨Ê±Æ÷´Ó0¼ÆÊıµ½1999£¬¼´Îª2000´Î£¬ÎªÒ»¸ö¶¨Ê±ÖÜÆÚ
  TIM_TimeBaseStructure.TIM_Prescaler = 72 -1 ;	    //¼´Îª1MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//ÉèÖÃÊ±ÖÓ·ÖÆµÏµÊı£º²»·ÖÆµ(ÕâÀïÓÃ²»µ½)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //ÏòÉÏ¼ÆÊıÄ£Ê½
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //ÅäÖÃÎªPWMÄ£Ê½1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //ÉèÖÃÌø±äÖµ£¬µ±¼ÆÊıÆ÷¼ÆÊıµ½Õâ¸öÖµÊ±£¬µçÆ½·¢ÉúÌø±ä
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //µ±¶¨Ê±Æ÷¼ÆÊıÖµĞ¡ÓÚCCR1_ValÊ±Îª¸ßµçÆ½
	
  TIM_OC4Init(TIM1, &TIM_OCInitStructure);	 //Ê¹ÄÜÍ¨µÀ1
  TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

  /* TIM4 enable counter */
  TIM_Cmd(TIM1, ENABLE);                   //
}

void TIM1_PWM_Init(void)
{
  TIM1_GPIO_Config();
	TIM1_Mode_Config();	
}


static void TIM2_GPIO_Config(void)  //A0
{
   GPIO_InitTypeDef GPIO_InitStructure;

	/* ÉèÖÃTIM1CLK Îª 72MHZ */
  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
  /*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1 |GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // ¸´ÓÃÍÆÍìÊä³ö
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

}

static void TIM2_Mode_Config(void)	
{
	u16 CCR2_Val = 0; 
	u16 CCR1_Val =0; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	/* PWMĞÅºÅµçÆ½Ìø±äÖµ */
       


/* ----------------------------------------------------------------------- 
    TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR+1)* 100% = 50%
    TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR+1)* 100% = 37.5%
    TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR+1)* 100% = 25%
    TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR+1)* 100% = 12.5%
  ----------------------------------------------------------------------- */

  /* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = 100 -1;       //µ±¶¨Ê±Æ÷´Ó0¼ÆÊıµ½1999£¬¼´Îª2000´Î£¬ÎªÒ»¸ö¶¨Ê±ÖÜÆÚ
  TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1 ;	    //¼´Îª1MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//ÉèÖÃÊ±ÖÓ·ÖÆµÏµÊı£º²»·ÖÆµ(ÕâÀïÓÃ²»µ½)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //ÏòÉÏ¼ÆÊıÄ£Ê½
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //ÅäÖÃÎªPWMÄ£Ê½1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	   //ÉèÖÃÌø±äÖµ£¬µ±¼ÆÊıÆ÷¼ÆÊıµ½Õâ¸öÖµÊ±£¬µçÆ½·¢ÉúÌø±ä
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //µ±¶¨Ê±Æ÷¼ÆÊıÖµĞ¡ÓÚCCR1_ValÊ±Îª¸ßµçÆ½
	
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);	 //Ê¹ÄÜÍ¨µÀ1
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //ÉèÖÃÌø±äÖµ£¬µ±¼ÆÊıÆ÷¼ÆÊıµ½Õâ¸öÖµÊ±£¬µçÆ½·¢ÉúÌø±ä
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);	 //Ê¹ÄÜÍ¨µÀ1
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM2, ENABLE);			   // Ê¹ÄÜTIM3ÖØÔØ¼Ä´æÆ÷ARR
  /* TIM4 enable counter */
  TIM_Cmd(TIM2, ENABLE);                   //
}

void TIM2_PWM_Init(void)
{
  TIM2_GPIO_Config();
	TIM2_Mode_Config();	
}
