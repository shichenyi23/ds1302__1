#ifndef STM_KEY_H
#define STM_KEY_H 			   
#include "sys.h" 
#include "delay.h"

#define key_run PAin(0)
#define key_shift PAin(1)
#define key_beep PAin(2)
#define key_up PAin(3)
#define key_down PAin(4)

void KEY_Init(void);
u8 KEY_Scan(void);
#endif
