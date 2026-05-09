/*
 * adc.c
 *
 *  Created on: 2026. 5. 9.
 *      Author: user
 */
#include "adc_poll.h"
#include "main.h"

//  resolution이 12bit이므로 4095 설정
#define AD_MAX ((1 << 12) - 1)

ADCPoll ADCPoll_Initialize(ADC_HANDLE adc_handle) {
	ADCPoll result = { .handle = adc_handle, .value = 0 };
	return result;
}

float ADCPoll_GetVolt(ADCPoll *self) {
	HAL_ADC_Start(self->handle);
	// 최대 100ms 까지 ADC 변환이 완료될때까지 대기
	HAL_ADC_PollForConversion(self->handle, 100);
	self->value = HAL_ADC_GetValue(self->handle);

	HAL_ADC_Stop(self->handle);

	// ADC -> 전압 변환
	return (float)((self->value*3.3)/AD_MAX);
}
