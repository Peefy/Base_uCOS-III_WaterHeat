
#ifndef _RELAY_H_
#define _RELAY_H_

#include "GPIOLIKE51.h"

#define RELAY1 PBout(3)
#define RELAY2 PBout(4)

#define RELAY PBout(13)
#define RELAY_ON  (RELAY = 0)
#define RELAY_OFF (RELAY = 1)

#define RELAY1_ON  (RELAY1 = 0)
#define RELAY1_OFF (RELAY1 = 1)
#define RELAY2_ON  (RELAY2 = 0)
#define RELAY2_OFF (RELAY2 = 1)



void RelayGpioInit(void);

#endif
