/*----------------------------------------------------------------------------
 * Name:    BlinkySingleLED_commanded_IE.c
 * Purpose: Turn on/off LED depending on input, managed via interrupt
 *----------------------------------------------------------------------------*/

#include <stm32f10x.h>                       /* STM32F103 definitions         */
#include "stm32f10x_it.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "pins_configuration.h"
int WAIT;
int IN_INT=0;

/*----------------------------------------------------------------------------
  wait function
 *----------------------------------------------------------------------------*/
void wait (void)  {
  int  d, j;
  WAIT = 1;
  for (j=0; j<5; j++)
		for (d = 0; d < 1000; d++);
  WAIT = 0;
}


/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/

int main(void) {
	
	RCC->APB2ENR	|=	RCC_APB2ENR_IOPCEN;			// Enable GPIOC clock
	GPIOC->CRL		=		0x00000333;							// PC.0..2 defined as Outputs (Signals to Engine)
	GPIOC->CRH		=		0x00003333;							// PC.8..11 defined as Outputs (Signals to Brakes)

  Configure_EXTI_GPIOB2();
	Configure_EXTI_GPIOB3();
	Configure_EXTI_GPIOB4();
	
	GPIOB->IDR		|= 1<<3;
	
	IN_INT=0;
	while(1){
			wait ();
			IN_INT=0;
	}
}
