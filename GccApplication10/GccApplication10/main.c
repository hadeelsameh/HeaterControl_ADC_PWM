/*
 * GccApplication10.c
 *
 * Created: 06/2021 16:42:38
 * Author : Hadeel
 */ 
#include "std_types.h"
#include "HeaterControl.h"
#include "micro_config.h"
#include <util/delay.h>

int main(void)
{
    
    
	uint8 vt=50;  /* supposed to be getted from temp maneger */
	init_HeaterControl();
	
    while(1)
    {
		Set_Heater_State(vt);
			
    }
}

