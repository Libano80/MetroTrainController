#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"

void Configure_EXTI_GPIOB2(void) {
    /* Set variables used */
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    
    RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// Enable clock for GPIOB
    
    /* Set pin as input */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; // GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource2);     
    
    EXTI_InitStruct.EXTI_Line = EXTI_Line2;	// PB15 is connected to EXTI_Line15
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;	// Enable interrupt
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	// Interrupt mode
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	// Triggers on rising and falling edge
    EXTI_Init(&EXTI_InitStruct);		// Add to EXTI
 
    /* Add IRQ vector to NVIC */
    NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;	// Set priority
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;		// Set sub priority
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;		// Enable interrupt
    NVIC_Init(&NVIC_InitStruct);				// Add to NVIC
}

void Configure_EXTI_GPIOB3(void) {
    /* Set variables used */
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    
    RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// Enable clock for GPIOB
    
    /* Set pin as input */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; // GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource3);     
    
    EXTI_InitStruct.EXTI_Line = EXTI_Line3;	// PB15 is connected to EXTI_Line15
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;	// Enable interrupt
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	// Interrupt mode
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	// Triggers on rising and falling edge
    EXTI_Init(&EXTI_InitStruct);		// Add to EXTI
 
    /* Add IRQ vector to NVIC */
    NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;	// Set priority
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;		// Set sub priority
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;		// Enable interrupt
    NVIC_Init(&NVIC_InitStruct);				// Add to NVIC
}

void Configure_EXTI_GPIOB4(void) {
    /* Set variables used */
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    
    RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// Enable clock for GPIOB
    
    /* Set pin as input */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; // GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource4);     
    
    EXTI_InitStruct.EXTI_Line = EXTI_Line4;	// PB15 is connected to EXTI_Line15
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;	// Enable interrupt
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	// Interrupt mode
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	// Triggers on rising and falling edge
    EXTI_Init(&EXTI_InitStruct);		// Add to EXTI
 
    /* Add IRQ vector to NVIC */
    NVIC_InitStruct.NVIC_IRQChannel = EXTI4_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;	// Set priority
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;		// Set sub priority
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;		// Enable interrupt
    NVIC_Init(&NVIC_InitStruct);				// Add to NVIC
}
