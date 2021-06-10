  /***************************************************************
 *  Source File: pwm.c
 *
 *  Description: PWM driver for ATMEGA32A
 *
 * Important Note:
 * 1.if you compile this file you will get errors on registers
 * names so ignore them as they are already pre-defined in avr liberary.
 * 2. I violate this rule
    (MISRA-C:2004 5.7/A) No identifier name should be reused ("TCCR2")  pwm.c   /pwmm   line 75 C/C++ Problem
    as I had made Deinit function and i have to use TCCR2 register and assign it to zero.
   3.I violate this rule
   (MISRA-C:2004 5.7/A) No identifier name should be reused ("OCR2")
   as I want to check if duty cycle 0 i will subtract 1 to see that pwm pin have no value
 *
 **************************************************************/
#include "pwm.h"


/*********************************************************************
* Function    : PWM_init();
*
* DESCRIPTION : Initializes the PWM in fast, non-inverting mode with 8 prescaler
*
* Return Value: Nothing
***********************************************************************/
void PWM_init(void)
{

     /* OC2 PIN TO BE OUTPUT */
     TIMER2_DDR |= ((uint8_t)1<<OC2_OUTPUT_SETTER);
     /*Disable Timer 2*/
     TCCR2 = DISABLE_MODULE_VALUE;
     /* TCCR2.
      * FOC2:This bit must be set to zero when TCCR2 is written when operating in PWM mode.
      * Bit 6,3  WGM20:21:  1 1 Fast PWM
      * Bit 5:4  COM20:21:  0 1 Clear OC2 on compare match, set OC2 at BOTTOM,(non-inverting mode)
      * Bit 2:0  CS20:21:22: Clock Select  0 1 0 clkI/O/8 (From prescaler )
      * We had chosen this prescaler as we will operate our application on 4MHz as F_CPU
      * and when using this equation: f_OCn_pwm=f_CPU/8*256
      * we get 1953.125Hz which is in the accepted range provided in statement
      * */
     TCCR2 = ((uint8_t)1<<WGM21)|((uint8_t)1<<WGM20)|((uint8_t)1<<COM21)|((uint8_t)1<<CS21);
     /* Initializing the timer with zero */
     TCNT2 = ZER0_INITIALIZER;

}

/****************************************************************************
* Function    : PWM_SetDutyCycle(U8_t DutyCycle)
*
* DESCRIPTION : Sets duty cycle for the  PWM
*
* PARAMETER 1 : The duty cycle value. A value between (0 %) and (100 %).
*
* Return Value: Nothing
******************************************************************************/
void PWM_SetDutyCycle(uint8_t DutyCycle)
{
    /*
     * duty cycle is represented by a number from 0->255
     */
    uint8_t PWM_actual_Duty ;



  PWM_actual_Duty = (DutyCycle * (uint8_t)TIMER_MAX_VALUE) / (uint8_t)DUTY_CYCLE_MAX_VALUE;
  /*Output Compare Register OCRx
   * contains an 8-bit value that is continuously compared
   * with the counter value (TCNTx). A match can be used to
   * generate an output compare interrupt
   **/
  if(PWM_actual_Duty==(uint8_t)0){
      OCR2 = (PWM_actual_Duty-(uint8_t)1);
  }
  else{
      OCR2 = PWM_actual_Duty;
  }

}
/*********************************************************************
* Function    : PWM_init();
*
* DESCRIPTION : make all register bits equal to zero
*
* Return Value: Nothing
***********************************************************************/
void PWM_Deinit(void)
{
    TCCR2=DISABLE_MODULE_VALUE;
}
