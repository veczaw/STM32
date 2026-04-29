#include "seven_segment.h"
#include "main.h"


#define ALL_SEGMENT			A_Pin | B_Pin | C_Pin | D_Pin | E_Pin | F_Pin | G_Pin | DOT_Pin

static unsigned int segments[10] = {
		A_Pin|B_Pin|C_Pin|D_Pin|E_Pin|F_Pin,			// 0
		B_Pin|C_Pin,									// 1
		A_Pin|B_Pin|D_Pin|E_Pin|G_Pin,					// 2
		A_Pin|B_Pin|C_Pin|D_Pin|G_Pin,					// 3
		B_Pin|C_Pin|F_Pin|G_Pin,						// 4
		A_Pin|C_Pin|D_Pin|F_Pin|G_Pin,					// 5
		A_Pin|C_Pin|D_Pin|E_Pin|F_Pin|G_Pin,			// 6
		A_Pin|B_Pin|C_Pin,								// 7
		A_Pin|B_Pin|C_Pin|D_Pin|E_Pin|F_Pin|G_Pin,		// 8
		A_Pin|B_Pin|C_Pin|F_Pin|G_Pin					// 9

};

void NineToZero(void) {
	unsigned int size = sizeof(segments) / sizeof(unsigned int);
	for (unsigned int i = 0; i < size; i++) {
		HAL_GPIO_WritePin(GPIOC, ALL_SEGMENT, GPIO_PIN_RESET);	// GPIO 모든 핀을 리셋
		HAL_GPIO_WritePin(GPIOC, segments[i], GPIO_PIN_SET);	// 각 숫자를 출력하기위한 Pin 활성화
		HAL_Delay(1000);
	}
}
