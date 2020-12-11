/*----------------------------------------------------------------------------
 * Name:    BrakingController.c
 * Purpose: Definition of the communication specifics with the Braking System
 *----------------------------------------------------------------------------*/

#include <stm32f10x.h>                       /* STM32F103 definitions         */
#include "BrakingController.h"
#include "pins_definition.h"

void initBrakingController(void) {
	RCC->APB2ENR	|=	RCC_APB2ENR_IOPCEN;			// Enable GPIOC clock
	GPIOC->CRH		=		0x00003333;							// PC.8..11 defined as Outputs (Signals to Brakes)
}

void enableMaxBrakingPower(void) {
	GPIOC->ODR		&= ~(OUT_MED_BRAKING);			// Switch off the MED_POWER braking Pin
	GPIOC->ODR		|= (OUT_MAX_BRAKING);				// Switch on the MAX_POWER braking Pin
}

void enableMedBrakingPower(void) {
	GPIOC->ODR		&= ~(OUT_MAX_BRAKING);			// Switch off the MAX_POWER braking Pin
	GPIOC->ODR		&= ~(OUT_MIN_BRAKING);			// Switch off the MIN_POWER braking Pin
	GPIOC->ODR		|= (OUT_MED_BRAKING);				// Switch on the MED_POWER braking Pin
}

void enableMinBrakingPower(void) {
	GPIOC->ODR		&= ~(OUT_MED_BRAKING);			// Switch off the MED_POWER braking Pin
	GPIOC->ODR		|= (OUT_MIN_BRAKING);				// Switch on the MIN_POWER braking Pin
}

void disableBraking(void) {
	GPIOC->ODR		&= ~(OUT_MAX_BRAKING);			// Switch off the MAX_POWER braking Pin
	GPIOC->ODR		&= ~(OUT_MED_BRAKING);			// Switch off the MED_POWER braking Pin
	GPIOC->ODR		&= ~(OUT_MIN_BRAKING);			// Switch off the MIN_POWER braking Pin
}

void enableEmergencyBrakingPower(void) {
	disableBraking();													// Disable other braking Pins
	GPIOC->ODR		|= (OUT_EMERG_BRAKING);			// Switch on the EMERGENCY braking Pin
}
