/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE & Simon Santacatterina
 * @brief          : Main program body for GPIO input configuration
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

// Custom implementation from here.

// Using all the structures defined by STM and ARM, and build on top.
#include <stm32f4xx.h>

// The values setting up bits in the registers.
#define GPIOAEN (1U<<0)
#define GPIOCEN (1U<<2)

#define PIN5	(1U<<5)
#define PIN13	(1U<<13)

#define LED_PIN PIN5
#define BTN_PIN PIN13
// Input Implementation for GPIO

int main()
{
	/*Enable clock access for GPIOA and GPIOC*/
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;

	/*Set PA5 as output pin*/
	GPIOA->MODER |= (1U<<10); // OR set MODER bit 10 to 1
	GPIOA->MODER &=~ (1U<<10); // NEG and AND set MODER bit 11 to 0

	/*Set PC13 as input pin*/
	GPIOC->MODER &=~ (1U<<26); // NEG and AND set MODER bit 26 to 0
	GPIOC->MODER &=~ (1U<<27); // NEG and AND set MODER bit 27 to 0

	while(1)
	{
		/*Check if the BTN is pressed (active low)*/
		if(GPIOC->IDR & BTN_PIN)
		{
			GPIOA->BSRR = LED_PIN;
		}
		else
		{
			GPIOA->BSRR = (1U<<21);
		}
	}
}
