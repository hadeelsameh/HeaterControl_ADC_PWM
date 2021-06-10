/*
 * HeaterControl.c
 *
 *  Created on: Jun 2021
 *      Author: Hadeel 
 */
#include "std_types.h"
#include "HeaterControl.h"
#include "pwm.h" 
#include "ADC.h" 

extern uint16 ADC_Result;
extern uint8 flag;

void init_HeaterControl(void){
    PWM_init();
    ADC_init();
}


void Set_Heater_State(uint8 vt){
	uint8 Duty_Cycle=0;
    float64 vr= 0;
    vr=get_vr_value();
    Duty_Cycle=(  (((((vr*2)/10.0)*vt)/10.0) )*10 );
    PWM_SetDutyCycle(Duty_Cycle);
}



float64 get_vr_value(void){
	float64 vr =0.0;
	ADC_readChannel();
	_delay_ms(1);
	if(flag == 1){
	   vr=(ADC_Result*5/1023);
	   flag=0;
	   return vr;
   }else{
	   /* do nothing*/
   }
}

