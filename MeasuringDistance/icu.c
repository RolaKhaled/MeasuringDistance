#include"icu.h"
#include<avr/io.h>
#include<avr/interrupt.h>
#include"common_macros.h"

static volatile void(*g_callBackPtr)(void) = NULL_PTR;

ISR(TIMER1_CAPT_vect){
	if(g_callBackPtr != NULL_PTR){
		(*g_callBackPtr)();
	}
}

void ICU_init(const ICU_Config *config_ptr){
	CLEAR_BIT(DDRD,6);
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	TCCR1B = (TCCR1B & 0xBF) | ((config_ptr->edge)<<6);
	TCCR1B = (TCCR1B & 0xF8) | (config_ptr->clk);
	TCNT1 = 0;
	ICR1 = 0;
	SET_BIT(TIMSK,5);
}

void ICU_setCallBack(void (*function_ptr)(void)){
	g_callBackPtr = function_ptr;
}

void ICU_setEdgeDetectionType(ICU_EdgeSelect edge){
	TCCR1B = (TCCR1B & 0xBF) | (edge<<6);
}

uint16 ICU_getInputCaptureValue(void){
	return ICR1;
}

void ICU_clearTimerValue(void){
	TCNT1 = 0;
}

void ICU_deInit(void){
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;
	CLEAR_BIT(TIMSK,5);
	g_callBackPtr = NULL_PTR;
}
