/**
 *********************************************************************************
 * @file      main.c
 * @author    Simon Santacatterina
 * @brief     STM32CubeIDE Main file for LED configuration
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
 *********************************************************************************
 */

//Bare-metal implementation

// AHB1PERIPH
#define PERIPH_BASE				(0x40000000UL)
#define AHB1PERIPH_OFFSET 		(0x00020000UL)
#define AHB1PERIPH_BASE 		(PERIPH_BASE + AHB1PERIPH_OFFSET)

// RCC - Module in charge of enabling each bus to the clock
#define RCC_OFFSET 				(0x00003800UL)
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1EN_R_OFFSET			(0x30UL)
#define RCC_AHB1EN_R			(*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))

// GPIOA
#define GPIOA_OFFSET 			(0x0000UL)		// Created for sake of clarity
#define GPIOA_BASE				(AHB1PERIPH_BASE + GPIOA_OFFSET)

// Mode register
#define MODE_R_OFFSET			(0x00UL)
#define GPIOA_MODE_R			(*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))

// Output data register
#define OD_R_OFFSET				(0x14UL)
#define GPIOA_OD_R				(*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))

// Setting the values
#define GPIOAEN					(1U<<0)
#define PIN5					(1U<<5)
#define LED_PIN					PIN5

int main(void)
{
	/* 1. Enable clock access to the GPIO */
	RCC_AHB1EN_R |= GPIOAEN;
	/* 2. Set the PA5 as output pin */
	GPIOA_MODE_R |= (1U<<10); //bit 10 to 1 for selecting output mode
	GPIOA_MODE_R &=~(1U<<11);

	while(1)
	{
		/* 3. Set the PA5 high (light up the LED) */
		// GPIOA_OD_R |= LED_PIN;

		/* 4. Toggle PA5, blinking the LED using delay*/
		GPIOA_OD_R ^= LED_PIN;
		for(int i = 0; i < 100000; i++){}
	}
}





