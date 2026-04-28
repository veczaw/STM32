/*
 * led.c
 *
 *  Created on: 2026. 4. 27.
 *      Author: user
 */

#include "led.h"
#include "main.h"

static void delay_int_count(volatile unsigned int nTime);
static void hal_led_toggle(int delay_ms);
static void reg_led_toggle(volatile unsigned int delay);

void Led_Toggle(enum led_opt opt, unsigned int delay_ms) {
	switch(opt) {
	case HAL:
		hal_led_toggle(delay_ms);
	case REGISTER:
		reg_led_toggle(delay_ms);
		break;
	}
}

static void hal_led_toggle(int delay_ms) {
	HAL_GPIO_TogglePin(GPIOC, LED1_Pin|LED2_Pin|LED4_Pin);
	HAL_Delay(1000);
}

#define rRCC_AMB1ENR *(volatile unsigned*)0x40023830		// Peripheral Clock Enable Register(RCC_AMB1ENR)
#define rGPIOC_MODER *(volatile unsigned*)0x40020800		// GPIO Port Mode Register
#define rGPIOC_OTYPER *(volatile unsigned*)0x40020804		// GPIO Port Output Type Register
#define rGPIOC_OSPEEDR *(volatile unsigned*)0x40020808		// GPIO Port Output Speed Register
#define rGPIOC_PUPDR *(volatile unsigned*)0x4002080C		// GPIO Port pull-up/pull-down Register
#define rGPIOC_ODR *(volatile unsigned*)0x40020814			// GPIO Port Output Data Register

#define GPIO_CLOCK_ENABLE		(1 << 2)
#define SET_GPIO_MODE_GENERAL_PURPOSE_MODE  (1 << 14 | 1 << 12 | 1 << 10 | 1 << 8 | 1 << 6 | 1 << 4 | 1 << 2 | 1)

static void delay_int_count(volatile unsigned int nTime) {
	for (; nTime > 0; nTime--);
}

static void reg_led_toggle(volatile unsigned int delay) {
	rRCC_AMB1ENR |= GPIO_CLOCK_ENABLE;		// GPIO Clock Enable
	rGPIOC_MODER |= SET_GPIO_MODE_GENERAL_PURPOSE_MODE; // GPIO 모드를 General Purpose Mode로 설정
	rGPIOC_OTYPER = 0x00000000;	// GPIO output type을 모두 push-pull (reset state)로 설정
	rGPIOC_OSPEEDR = 0x00000000; // GPIO output speed를 모두 low speed로 설정
	rGPIOC_PUPDR = 0x00000000;	// GPIO Pull-up/Pull-down을 모두 No pull-up, pull-down으로 설정

	while (1) {
		rGPIOC_ODR = 0xffff;  			// LED on (PC0~PC15 포트에 전부 신호 활성화)
		delay_int_count(delay);
		rGPIOC_ODR = 0x0000;			// LED off (PC0~PC15 포트에 전부 신호 비활성화)
		delay_int_count(delay);
	}
}


