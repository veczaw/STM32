/*
 * adc.h
 *
 *  Created on: 2026. 5. 9.
 *      Author: user
 */

#ifndef INC_ADC_POLL_H_
#define INC_ADC_POLL_H_

#include <stdint.h>

typedef void *ADC_HANDLE;

typedef struct ADCPoll {
	ADC_HANDLE handle;	// adc 핸들
	uint32_t value;		// adc 값
} ADCPoll;

ADCPoll ADCPoll_Initialize(ADC_HANDLE uart_def);

// adc 값을 100ms
float ADCPoll_GetVolt(ADCPoll *self);

#endif /* INC_ADC_POLL_H_ */
