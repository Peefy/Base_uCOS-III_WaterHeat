
#include "TempControl.h"
#include "relay.h"
#include "ds18b20.h"
#include "stdbool.h"
#include "flash.h"
#include "breathLED.h"

#define ABS(x) (((x) > 0) ? (x) : (-x))

TempPara_t TempPara = {100,0};
bool controlEnable = false;

void GetTempValue(void);

char controlTime = 0;
void TempControlTimerDelegate(void)
{
	if(++ controlTime >= CONTROL_MS / TIM_MS)
	{
		GetTempValue();
		if(controlEnable == true)
		{		
			int tempCha = 44;
			if(TempPara.Set >= 200 && TempPara.Set < 300)
			{
				if(TempPara.Now > (TempPara.Set - 44))
				{
					RELAY_OFF;
					BreathLedEnable = false;
				}				
			else
			{
				RELAY_ON;
				BreathLedEnable = true;
			}
		}
			if(TempPara.Set >= 300 && TempPara.Set < 400)
			{
				if(TempPara.Now > (TempPara.Set - 31))
				{
					RELAY_OFF;
					BreathLedEnable = false;
				}				
			else
			{
				RELAY_ON;
				BreathLedEnable = true;
			}
		}
			if(TempPara.Set >= 400 && TempPara.Set < 600)
			{
				if(TempPara.Now > (TempPara.Set - 18))
				{
					RELAY_OFF;
					BreathLedEnable = false;
				}				
			else
			{
				RELAY_ON;
				BreathLedEnable = true;
			}
		}
			if(TempPara.Set >= 600)
			{
				if(TempPara.Now > (TempPara.Set - 11))
				{
					RELAY_OFF;
					BreathLedEnable = false;
				}				
			else
			{
				RELAY_ON;
				BreathLedEnable = true;
			}
		}
		}
		controlTime = 0;
	}
}

char getTime = 0;
u16 tempLast = 0;
void GetTempValue(void)
{
	if(++ getTime >= GET_TEMP_MS/CONTROL_MS )
	{
		WriteFlash();
		tempLast = DS18B20_Get_Temp();
		//tempLast = 230;
		if(tempLast > TEMP_MAX || tempLast < TEMP_MIN)
			return;
		if(TempPara.Now >TEMP_MIN && ABS(tempLast - TempPara.Now )> 9)
			return;
    TempPara.Now = tempLast; 
		controlEnable = true;
		getTime = 0;
	}
}

