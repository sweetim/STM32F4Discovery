#ifndef __GPIO_OUT_H__
#define __GPIO_OUT_H__

#include "stm32f4xx.h"

#include <stdbool.h>

typedef struct {
	uint32_t gpio_clock;
	GPIO_TypeDef* gpio_port;
	uint16_t gpio_pin;
} Gpio_Out;

void gpio_out_initialize(Gpio_Out *instance);
void gpio_out_set(Gpio_Out *instance, bool status);

#endif // __GPIO_OUT_H__