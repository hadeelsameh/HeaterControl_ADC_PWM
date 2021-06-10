/***************************************************************
 *  Source File: PWM_cfg.h
 *
 *  Description: PWM driver configuration for ATMEGA32A
 *
 **************************************************************/
#ifndef PWM_CFG_H_
#define PWM_CFG_H_
#include <avr/io.h>

typedef unsigned char uint8_t;
#define DISABLE_MODULE_VALUE 0x00
/* Timer DDR */
#define TIMER2_DDR	(DDRD)
/* Out compare pin */
#define OC2_OUTPUT_SETTER  7

#define ZER0_INITIALIZER                0x00
/* Max counts of timer0 is 2^8=255 */
#define TIMER_MAX_VALUE                 255
/* max Percentage Value (100%) */
#define DUTY_CYCLE_MAX_VALUE            100

#endif /* PWM_CFG_H_ */
