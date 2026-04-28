/*
 * led.h
 *
 *  Created on: 2026. 4. 27.
 *      Author: user
 */

#ifndef INC_LED_H_
#define INC_LED_H_

enum led_opt {
	HAL,
	REGISTER
};

void Led_Toggle(enum led_opt opt, unsigned int delay_ms);

#endif /* INC_LED_H_ */
