#include <stm32f10x.h>                       /* STM32F103 definitions         */
#include "LeverController.h"
#include "pins_definition.h"

void initLeverController(void) {
	RCC->APB2ENR	|=	RCC_APB2ENR_IOPBEN;			// Enable GPIOB clock
	GPIOB->CRL		=		0x88888800;							// PB.2..7 defined as Inputs
	GPIOB->CRH		=		0x00000008;							// PB.8 defined as Input
}

unsigned int isLeverIdle(void) {
	return GPIOB->IDR & PIN_IDLE_LEVER;				// Check if the Lever is in IDLE position
}
