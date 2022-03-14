/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE & Simon Santacatterina
 * @brief          : Main program body for GPIO output configuration
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

//Custom implementation from here.

//This time using all the structures defined by STM and ARM, and build on top.
#include <stm32f4xx.h>

// The values setting up the registers.
#define GPIOAEN (1U<<0)
#define PIN5	(1U<<5)
#define LED_PIN PIN5

// In this new implementation, no use of toggle operator, just Bit Set Reset Register (BSRR)

int main()
{
	RCC->AHB1ENR |= GPIOAEN; //RCC register structure

	GPIOA->MODER |= (1U<<10); // OR set MODER bit 10 to 1
	GPIOA->MODER &=~ (1U<<10); // NEG and AND set MODER bit 11 to 0

	while(1)
	{
		GPIOA->BSRR = LED_PIN;
		for(int i = 0; i <100000; i++){}

		GPIOA->BSRR = (1U<<21);
		for(int i = 0; i <100000; i++){}
	}
}
