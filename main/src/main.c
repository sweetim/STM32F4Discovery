#include "driver/gpio_out/gpio_out.h"

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


int main(void)
{
	SystemInit();
	
	gpio_out_initialize(&green_led_gpio);
	gpio_out_initialize(&orange_led_gpio);
	gpio_out_initialize(&red_led_gpio);
	gpio_out_initialize(&blue_led_gpio);
	
	while(true) {
		gpio_out_set(&green_led_gpio, true);
		gpio_out_set(&orange_led_gpio, true);
		gpio_out_set(&red_led_gpio, true);
		gpio_out_set(&blue_led_gpio, true);
	}
	
	
	return 0;
}