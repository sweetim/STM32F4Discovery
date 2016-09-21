#include "gpio_out.h"

void gpio_out_initialize(Gpio_Out *instance)
{
	RCC_AHB1PeriphClockCmd(instance->gpio_clock, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
		
	GPIO_InitStructure.GPIO_Pin = instance->gpio_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(instance->gpio_port, &GPIO_InitStructure);	
}

void gpio_out_set(Gpio_Out *instance, bool status)
{
	if (status) {
        GPIO_SetBits(instance->gpio_port, instance->gpio_pin);

        return;
    }

    GPIO_ResetBits(instance->gpio_port, instance->gpio_pin);
}