#ifndef __TIMER_H__
#define __TIMER_H__

#include "stm32f4xx.h"

typedef void(*timer_handler)(void);

typedef enum {
	Timer_2,
	ALL_TIMER_TYPE
} Timer_Type;

typedef struct {
	uint32_t peripheral_clock;
	uint32_t irq_type;
	uint8_t irq_level;
	uint8_t irq_sub_level;
	uint16_t prescale;
	uint32_t period;
} Timer_Settings;

typedef struct {
	TIM_TypeDef *timer_type;
	Timer_Settings settings;
} Timer;

void timer_initialize(Timer *instance);
void timer_start(Timer *instance);
void timer_register_handler(timer_handler handler, Timer_Type type);

#endif // __TIMER_H__