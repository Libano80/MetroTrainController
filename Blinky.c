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
#include "RTL.h"
#include "EXTI_pins_configuration.h"
#include "pins_definition.h"
#include "tick.h"

extern volatile int T1 = 0, IDLE = 1;

volatile int Eid = 0x01;

OS_TID Tid;         // Task1 (phase manager) id

volatile int current_Pin;

__task void Task1(void) {
	//wake up every 10 ms
	//react to events

	unsigned int last_Pin = PIN_IDLE_LEVER;					// Value of the last Pin enabled
	int ticks_max_accel = -1;
	
	//os_itv_set(10);
	while(1) {
		os_evt_wait_or(Eid, 0xFFFF);
		T1 = 1; IDLE = 0;
		current_Pin = GPIOB->IDR;											// Update the value of the Pin currently enabled
		if(current_Pin != last_Pin) {
			switch(current_Pin) {
				case PIN_MAX_BRAKING:
					GPIOC->ODR	&= ~(OUT_MED_BRAKING);			// Switch off the MED_POWER braking Pin
					GPIOC->ODR	|= (OUT_MAX_BRAKING);				// Switch on the MAX_POWER braking Pin
					break;
				case PIN_MED_BRAKING:
					GPIOC->ODR	&= ~(OUT_MAX_BRAKING);			// Switch off the MAX_POWER braking Pin
					GPIOC->ODR	&= ~(OUT_MIN_BRAKING);			// Switch off the MIN_POWER braking Pin
					GPIOC->ODR	|= (OUT_MED_BRAKING);				// Switch on the MED_POWER braking Pin
					break;
				case PIN_MIN_BRAKING:
					GPIOC->ODR	&= ~(OUT_MED_BRAKING);			// Switch off the MED_POWER braking Pin
					GPIOC->ODR	|= (OUT_MIN_BRAKING);				// Switch on the MIN_POWER braking Pin
					break;
				case PIN_IDLE_LEVER:
					GPIOC->ODR	&= ~(OUT_MIN_BRAKING);			// Switch off the MIN_POWER braking Pin
					GPIOC->ODR	&= ~(OUT_MIN_ACCEL);				// Switch off the MIN_POWER engine Pin
					break;
				case PIN_MIN_ACCEL:
					GPIOC->ODR	&= ~(OUT_MED_ACCEL);				// Switch off the MED_POWER engine Pin
					GPIOC->ODR	|= (OUT_MIN_ACCEL);					// Switch on the MIN_POWER engine Pin
					break;
				case PIN_MED_ACCEL:
					GPIOC->ODR	&= ~(OUT_MAX_ACCEL);				// Switch off the MAX_POWER engine Pin
					GPIOC->ODR	&= ~(OUT_MIN_ACCEL);				// Switch off the MIN_POWER engine Pin
					GPIOC->ODR	|= (OUT_MED_ACCEL);					// Switch on the MED_POWER engine Pin
					ticks_max_accel = -1;										// Reset the number of ticks	
					//tickReset();														// Reset the number of ticks (avoid oversize faults)
					break;
				case PIN_MAX_ACCEL:
					GPIOC->ODR	&= ~(OUT_MED_ACCEL);				// Switch off the MED_POWER engine Pin
					GPIOC->ODR	|= (OUT_MAX_ACCEL);					// Switch on the MIN_POWER engine Pin
					ticks_max_accel = tickGet();						// Read the actual number of ticks
					break;
			}
			last_Pin = current_Pin;
		}
		
		if(current_Pin == PIN_MAX_ACCEL & (tickGet() - ticks_max_accel) == 400) {			// If the MAX_ACCEL Pin has been on for 4s (400 * 10ms = 4s)
			GPIOC->ODR	&= ~(OUT_MAX_ACCEL);																							// Switch off the MAX_POWER engine Pin
			GPIOC->ODR	|= (OUT_MED_ACCEL);																								// Switch on the MED_POWER engine Pin
			ticks_max_accel = -1;																													// Reset the ticks_max_accel variable
		}
	}
}

__task void TaskInit(void) {
  //T2id = os_tsk_create( Task2, 10 );	
  Tid = os_tsk_create( Task1, 10 );
  //TBid = os_tsk_create( TaskB, 1 );
  //T3id = os_tsk_create( Task3, 80 );
	//TsimIdm = os_tsk_create( TaskSim, 99 );

  os_tsk_delete_self();      // kills self
}


/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/

int main(void) {
	//unsigned int in_pin = 1<<5;
	
	RCC->APB2ENR	|=	RCC_APB2ENR_IOPCEN;			// Enable GPIOC clock
	GPIOC->CRL		=		0x00000333;							// PC.0..2 defined as Outputs (Signals to Engine)
	GPIOC->CRH		=		0x00003333;							// PC.8..11 defined as Outputs (Signals to Brakes)

	tickInit();
	
  //Configure_EXTI_GPIOB2();
	//Configure_EXTI_GPIOB3();
	//Configure_EXTI_GPIOB4();
	//Configure_EXTI_GPIOB5();
	//Configure_EXTI_GPIOB6();
	//Configure_EXTI_GPIOB7();
	//Configure_EXTI_GPIOB8();
	RCC->APB2ENR	|=	RCC_APB2ENR_IOPBEN;
	GPIOB->CRL		=		0x88888800;
	GPIOB->CRH		=		0x00000008;
	
	os_sys_init( TaskInit );
	//while(1){
	//		wait ();
	//		IN_INT=0;
	//}
}
