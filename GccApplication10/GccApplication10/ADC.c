 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega32 ADC driver
 *
 * Author: Toqa&ghada
 *
 *******************************************************************************/
#include <avr/io.h>

#include "ADC_Cfg.h"
#include "ADC.h"
#include "ADC_Lcfg.h"

#define ADC_Register        *((volatile uint16*) 0x24)
uint16 ADC_Result;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
#define ADC_SFIOR_MASK_VALUE						0x1F
#define ADC_RIGHT_ADJ_REG_OFFSET_VALUE              8
#define ADC_RIGHT_ADJ_LOW_PART_OFFSET_VALUE_8_BIT   2
#define ADC_RIGHT_ADJ_HIGH_PART_OFFSET_VALUE_8_BIT  6
#define ADC_LEFT_ADJ_HIGH_PART_SHIFT_OFFSET         2
#define ADC_LEFT_ADJ_LOW_PART_SHIFT_OFFSET          6
#define ADC_INTERRUPT_FLAG_BIT_LOCATION_IN_ADCSRA_REG 4


uint16_t ADC_Readings;
static void (*Conv_ptr)(void);
typedef uint8 Adc_ConfigurationStrSizeType;
void ADC_init(void)
{
	Adc_ConfigurationStrSizeType local_u8LoopCounter=0;
	for(local_u8LoopCounter=0 ; local_u8LoopCounter < ADC_NUMBER_OF_CONFIGURED_ADCS ; ++local_u8LoopCounter)
	{
		/*set ADMUX values*/
		 ADMUX = (gastr_AdcConfigArr[local_u8LoopCounter].Adc_InitalChannel | gastr_AdcConfigArr[local_u8LoopCounter].Adc_RegisterAdjustment | gastr_AdcConfigArr[local_u8LoopCounter].Adc_VoltageReference);

		/*check AutoTrigger value of it's Enabled then select Set trigger source in SFIOR*/
		if(gastr_AdcConfigArr[local_u8LoopCounter].Adc_AutoTriggerState==ADC_AUTOTRIGGER_ENABLED)
		{
			/*set AutoTrigger source in the SFIOR*/
			SET_VALUE_REG(ADCSRA , ADC_SFIOR_MASK_VALUE , gastr_AdcConfigArr[local_u8LoopCounter].Adc_AutoTriggerSources);
		}

		/*set Values in the ADCSRA */
		ADCSRA  = (gastr_AdcConfigArr[local_u8LoopCounter].Adc_Prescaler | gastr_AdcConfigArr[local_u8LoopCounter].Adc_InterruptState | gastr_AdcConfigArr[local_u8LoopCounter].Adc_AutoTriggerState | gastr_AdcConfigArr[local_u8LoopCounter].Adc_IntialState);
	  Conv_ptr = gastr_AdcConfigArr[local_u8LoopCounter].Conversion_CompleteFunptr;
		SREG  |= (1<<7);
	}
	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 */
      
/*	CLEAR ADC INTERRUPT FLAG	*/
	SET_BIT(ADCSRA , ADIF);

	ADCSRA |= (1<<ADEN);
	
}



uint16 ADC_readChannel(void){
	
	/*	CLEAR MUX	*/
	//uint16 LOC_u16Result = 0;
	//channel_num &= 0b00011111;
	//ADMUX &= 0xE0;
	//ADMUX |= channel_num ;
	SET_BIT(ADCSRA,ADSC);
	
}
uint16 ADC_u16UpdateValue(void)
{
	//return the previous reading of the ADC channel
	return ADC_Register;
}

ISR (ADC_vect)
{
	//update ADC result
	ADC_Result = ADC_u16UpdateValue();
	Conv_ptr();
	
	SET_BIT(ADCSRA , ADIF);
}