#include "timer.h"

static volatile timer_handler all_timer_handler[ALL_TIMER_TYPE] = { 0 };

static void nvic_timer_configuration(Timer_Settings *settings);
static void timer_configuration(Timer *instance);

void timer_initialize(Timer *instance)
{
	RCC_APB1PeriphClockCmd(instance->settings.peripheral_clock, ENABLE);
	
	nvic_timer_configuration(&instance->settings);
	timer_configuration(instance);
}

static void nvic_timer_configuration(Timer_Settings *settings)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = settings->irq_type;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = settings->irq_level;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = settings->irq_sub_level;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);
}

static void timer_configuration(Timer *instance)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    TIM_TimeBaseStructure.TIM_Period = instance->settings.period;
    TIM_TimeBaseStructure.TIM_Prescaler = instance->settings.prescale;

    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(instance->timer_type, &TIM_TimeBaseStructure);

    TIM_ITConfig(instance->timer_type, TIM_IT_Update, ENABLE);
}

void timer_start(Timer *instance)
{
	TIM_Cmd(instance->timer_type, ENABLE);  
}

void timer_register_handler(timer_handler handler, Timer_Type type)
{
	all_timer_handler[type] = handler;
}

static void execute_timer_handler(Timer_Type type) 
{
	 if (all_timer_handler[type] != 0) {
		all_timer_handler[type]();
	}	
}

void TIM2_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	execute_timer_handler(Timer_2);
}