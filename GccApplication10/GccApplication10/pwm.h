/***************************************************************
 *  Source File: PWM.h
 *
 *  Description: PWM driver for ATMEGA32A
 *
 **************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "pwm_cfg.h"

/*************************************************
 *  API functions
 *************************************************/

void PWM_init(void);
void PWM_SetDutyCycle(uint8_t DutyCycle);
void PWM_Deinit(void);
#endif /* PWM_H_ */
