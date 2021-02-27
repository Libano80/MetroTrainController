/*----------------------------------------------------------------------------
 * Name:    LeverController.c
 * Purpose: Definition of the communication specifics with the Driver Lever
 *----------------------------------------------------------------------------*/

#include <stm32f10x.h>                       /* STM32F103 definitions         */
#include "LeverController.h"
#include "pins_definition.h"
#include "TestSimulation.h"

#ifdef TEST_MODE
extern unsigned int lever_position;
#endif

void initLeverController(void) {
	RCC->APB2ENR	|=	RCC_APB2ENR_IOPBEN;			// Enable GPIOB clock
	GPIOB->CRL		=		0x88888800;							// PB.2..7 defined as Inputs
	GPIOB->CRH		=		0x00000008;							// PB.8 defined as Input
}

unsigned int getLeverCurrentPosition(void) {
	#ifdef TEST_MODE
	return lever_position;
	#else
	return GPIOB->IDR;
	#endif
}

unsigned int isLeverIdle(void) {
	#ifdef TEST_MODE
	return lever_position == PIN_IDLE_LEVER;
	#else
	return GPIOB->IDR & PIN_IDLE_LEVER;				// Check if the Lever is in IDLE position
	#endif
}
