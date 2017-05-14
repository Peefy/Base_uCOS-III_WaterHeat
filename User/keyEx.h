
#ifndef _KEYEX_H_
#define _KEYEX_H_

#include <stdbool.h>

#define KEYEX_DOWN_TIME 1
#define KEYEX_HOLD_TIME 45

typedef struct
{
	bool Key1PressDown;
	bool Key2PressDown;
	bool Key3PressDown;
}KeyStatus_t;

typedef struct
{
	char DownTime;
	char LongDownDelay;
	bool PressDown;
	void (*Event)(void);
}Key_t;

void KeyExtralInit(void);
KeyStatus_t GetKeyExtralTotalStatus(void);
void KeyExTimerDelegate(void);

#endif
