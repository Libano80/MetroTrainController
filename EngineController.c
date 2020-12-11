/*----------------------------------------------------------------------------
 * Name:    EngineController.c
 * Purpose: Definition of the communication specifics with the Engine
 *----------------------------------------------------------------------------*/

#include <stm32f10x.h>                       /* STM32F103 definitions         */
#include "EngineController.h"
#include "pins_definition.h"

void initEngineController(void) {
	RCC->APB2ENR	|=	RCC_APB2ENR_IOPCEN;			// Enable GPIOC clock
	GPIOC->CRL		=		0x00000333;							// PC.0..2 defined as Outputs (Signals to Engine)
}

void enableMaxEnginePower(void) {
	GPIOC->ODR		&= ~(OUT_MED_ACCEL);				// Switch off the MED_POWER engine Pin
	GPIOC->ODR		|= (OUT_MAX_ACCEL);					// Switch on the MIN_POWER engine Pin
}

void enableMedEnginePower(void) {
	GPIOC->ODR		&= ~(OUT_MAX_ACCEL);				// Switch off the MAX_POWER engine Pin
	GPIOC->ODR		&= ~(OUT_MIN_ACCEL);				// Switch off the MIN_POWER engine Pin
	GPIOC->ODR		|= (OUT_MED_ACCEL);					// Switch on the MED_POWER engine Pin
}

void enableMinEnginePower(void) {
	GPIOC->ODR		&= ~(OUT_MED_ACCEL);				// Switch off the MED_POWER engine Pin
	GPIOC->ODR		|= (OUT_MIN_ACCEL);					// Switch on the MIN_POWER engine Pin
}

void disableEngine(void) {
	GPIOC->ODR		&= ~(OUT_MAX_ACCEL);				// Switch off the MAX_POWER engine Pin
	GPIOC->ODR		&= ~(OUT_MED_ACCEL);				// Switch off the MED_POWER engine Pin
	GPIOC->ODR		&= ~(OUT_MIN_ACCEL);				// Switch off the MIN_POWER engine Pin
}
