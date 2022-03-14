/**
 *********************************************************************************
 * @file      main.c
 * @author    Simon Santacatterina
 * @brief     STM32CubeIDE Main file for LED configuration (version 2)
 *********************************************************************************
 * First problem to solve : where is the LED connected? PA5
 * Port: A
 * Pin:  5
 *********************************************************************************
 * Theory explanation
 *
 * 1) Memory mapping
 * On the board, addresses are used to access and set the hardware.
 * Peripherals have addresses and inside those peripherals there are registers
 * with particular addresses for various uses, that you access by offsets.
 *
 * Informations as follows : Bus - Boundary address - Peripheral (hardware)
 *
 * 2) Clock bus
 * What is the bus? Buses lead the clock to the peripherals.
 * Different types of buses depending on the micro-controller,
 * some buses are faster than others (AHP buses faster than APB buses).
 * For a global overview, check the block diagram (STM32F411xC/xE block diagram).
 *
 * 3) Structures : predefined by STM in header files so no need to compute
 * all offsets.
 *********************************************************************************
 */

//Implementation using predefined structures
#include <stdint.h>

// BASE registers addresses
// AHB1PERIPH
#define PERIPH_BASE				(0x40000000UL)
#define AHB1PERIPH_OFFSET 		(0x00020000UL)
#define AHB1PERIPH_BASE 		(PERIPH_BASE + AHB1PERIPH_OFFSET)

// RCC - Module in charge of enabling each bus to the clock
#define RCC_OFFSET 				(0x00003800UL)
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)

// GPIOA
#define GPIOA_OFFSET 			(0x0000UL)		// Created for sake of clarity
#define GPIOA_BASE				(AHB1PERIPH_BASE + GPIOA_OFFSET)



// This time compare to 0_led_toggle_addr, the structures for registers are used.
// The number of members in each structures depends on the hardware set up.
typedef struct {
	volatile uint32_t DUMMY[12]; // Keep the offset consistent (until AHB1EN_R)
	volatile uint32_t AHB1EN_R;
}RCC_TypeDef;

typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t DUMMY[4]; // Keep the offset consistent (between MODER and ODR registers)
	volatile uint32_t ODR;
}GPIO_TypeDef;

// Then type cast the base values as RCC_TypeDef and GPIO_TypeDef
#define RCC						((RCC_TypeDef*)	RCC_BASE)
#define GPIOA					((GPIO_TypeDef*) GPIOA_BASE)



// Setting the values that will be used
#define GPIOAEN					(1U<<0) //   0b 0000 0000 0000 0000 0000 0000 0000 0001
#define PIN5					(1U<<5) //   0b 0000 0000 0000 0000 0000 0000 0010 0000
#define LED_PIN					PIN5


int main(void)
{
	/* 1. Enable clock access to the GPIO */
	RCC->AHB1EN_R |= GPIOAEN;

	/* 2. Set the PA5 as output pin */
	GPIOA->MODER |= (1U<<10); // Set bit 10 to 1 selecting output mode (OR)
	GPIOA->MODER &=~(1U<<11); // Set bit 11 to 0 selecting output mode (NEG then AND)

	while(1)
	{
		GPIOA->ODR ^= LED_PIN;
		for(int i = 0; i < 100000; i++){}
	}
}





