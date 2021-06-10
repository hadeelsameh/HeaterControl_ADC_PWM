#include "ADC_Cfg.h"
#include "ADC.h"
#include "ADC_Lcfg.h"


extern uint16 ADC_Result;
uint8 flag=0;
void END_OF_CONV_Call_Back(void);
void END_OF_CONV_Call_Back(void)   // ADC Conversion complete
{    
	flag=1; 
}



Adc_ConfigType gastr_AdcConfigArr[ADC_NUMBER_OF_CONFIGURED_ADCS]=
{
	{ADC_SINGLE_ENDED_ADC7                   ,          ADC_PRESCALER_8               ,               ADC_REG_RIGHT_ADJ              ,                  ADC_RESOLUTION_10_BIT                 ,               ADC_VREF_AREF                  ,         ADC_INTERRUPT_ENABLED                 ,         ADC_AUTOTRIGGER_DISABLED          ,            ADC_AUTO_TRIGGER_NONE            ,     ADC_CURRENT_STATE_ENABLED,&END_OF_CONV_Call_Back}
	/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
};
