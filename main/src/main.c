#include <stdbool.h>

#include "driver/gpio_out/gpio_out.h"
#include "driver/timer/timer.h"

static Gpio_Out green_led_gpio = {
	.gpio_clock = RCC_AHB1Periph_GPIOD,
	.gpio_port = GPIOD,
	.gpio_pin = GPIO_Pin_12
};

static Gpio_Out orange_led_gpio = {
	.gpio_clock = RCC_AHB1Periph_GPIOD,
	.gpio_port = GPIOD,
	.gpio_pin = GPIO_Pin_13
};

static Gpio_Out red_led_gpio = {
	.gpio_clock = RCC_AHB1Periph_GPIOD,
	.gpio_port = GPIOD,
	.gpio_pin = GPIO_Pin_14
};

static Gpio_Out blue_led_gpio = {
	.gpio_clock = RCC_AHB1Periph_GPIOD,
	.gpio_port = GPIOD,
	.gpio_pin = GPIO_Pin_15
};

static Timer timer_2 = {
	.timer_type = TIM2,
	.settings = {
		.peripheral_clock = RCC_APB1Periph_TIM2,
		.irq_type = TIM2_IRQn,
		.irq_level = 0,
		.irq_sub_level = 0,
		.prescale = 84 - 1,
		.period = 1000000
	}
};

static volatile bool red_status = false;

static void timer_2_handler(void)
{
	red_status = !red_status;
	gpio_out_set(&red_led_gpio, red_status);
}

int main(void)
{
	SystemInit();
	
	timer_initialize(&timer_2);
	
	gpio_out_initialize(&green_led_gpio);
	gpio_out_initialize(&orange_led_gpio);
	gpio_out_initialize(&red_led_gpio);	
	gpio_out_initialize(&blue_led_gpio);
	
	timer_start(&timer_2);
	timer_register_handler(timer_2_handler, Timer_2);
	
	while(true) {
		gpio_out_set(&green_led_gpio, true);
		gpio_out_set(&orange_led_gpio, true);
		
		gpio_out_set(&blue_led_gpio, true);
	}
	
	
	return 0;
}