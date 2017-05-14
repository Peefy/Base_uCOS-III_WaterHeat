#ifndef _PWM_H_
#define _PWM_H_

// TIM1_PWM A8 A9 A10 A11
// TIM2_PWM A0 A1 A2 A3  NO USE
// TIM3_PWM A6 A7 B0 B1
// TIM4_PWM B6 B7 B8 B9

#define pwmHz 999
                                                                                                 
void TIM3_PWM_Init(void);
void TIM4_PWM_Init(void);
void TIM1_PWM_Init(void);
void TIM2_PWM_Init(void);

#endif
