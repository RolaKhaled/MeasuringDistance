#include"lcd.h"
#include"icu.h"
#include"ultrasonic.h"
#include<avr/io.h>
#include<util/delay.h>

int main(void){
	uint16 distance=0;
	SREG|=(1<<7);
	LCD_init();
	Ultrasonic_init();
	LCD_displayString("Distance=     cm");

	while(1){

		distance= Ultrasonic_readDistance();
		LCD_moveCursor(0,9);
		LCD_integerToString(distance);
		if(distance<100){
			LCD_displayString(" ");
		}
		if(distance<1000){
			LCD_displayString("  ");
		}

	}
}
