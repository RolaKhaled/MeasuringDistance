#include"ultrasonic.h"
#include"icu.h"
#include"gpio.h"
#include"common_macros.h"
#include<util/delay.h>

uint16 g_EchoHighTime=0;
/*the readDistance function works when it is called two times, the first time it triggers the trig pin and waits till
 * the sound wave bounce back. The second time it calculates the distance*/

volatile uint8 g_flag1=0; /*flag to check if it is the first time to call the call back function or the second time*/
volatile uint8 g_flag2=0; /*flag to check if its the first time to call the readDistance function*/
void Ultrasonic_init(void){
	ICU_Config ICU_configurations = {F_CPU_8,RISING};
	ICU_init(&ICU_configurations);
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(TRIG_PORT_ID,TRIG_PIN_ID,PIN_OUTPUT);
}

void Ultrasonic_trigger(void){
	GPIO_writePin(TRIG_PORT_ID,TRIG_PIN_ID,LOGIC_HIGH);
	_delay_us(20);
	GPIO_writePin(TRIG_PORT_ID,TRIG_PIN_ID,LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void){
	uint16 distance;
	Ultrasonic_trigger();
	if(g_flag2 == 0){
		/*do nothing because the sound wave did not bounce back yet*/
	}
	if(g_flag2 == 1){
		distance = //(g_Time1/2)*(SPEED*(10^(-2)));
				g_EchoHighTime*0.017;
		g_flag2=0;
	}
	return distance;
}


void Ultrasonic_edgeProcessing(void){
	if(g_flag1 == 0){
			/*First interrupt means the echo got a rising edge so clear the timer to start counting the time from zero*/
			ICU_clearTimerValue();
			/*set edge detection to falling so when the the sound waves bounce back an echo gets a falling edge
			 * another interrupt happen*/
			ICU_setEdgeDetectionType(FALLING);
			/*increment the flag so the next interrupt this part is skipped*/
			g_flag1=1;
		}
		else if(g_flag1 == 1){
			/*Second interrupt: sound waves bounced back so get the timer value*/
			g_EchoHighTime = ICU_getInputCaptureValue();
			/*change the edge detection and set flag to zero to repeat the process*/
			ICU_setEdgeDetectionType(RISING);
			g_flag1 = 0;
			g_flag2 = 1;
		}
}
