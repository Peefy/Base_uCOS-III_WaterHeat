
#ifndef _TEMPCONTROL_H_
#define _TEMPCONTROL_H_

#include <stm32f10x.h>

#define TEMP_MAX 750
#define TEMP_MIN 100

#define TIM_MS 10
#define CONTROL_MS 100
#define GET_TEMP_MS 1000

typedef struct
{
	u16 Set;
	u16 Now;
}TempPara_t;

extern TempPara_t TempPara;
void TempControlTimerDelegate(void);

#endif

