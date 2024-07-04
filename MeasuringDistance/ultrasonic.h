
#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include"std_types.h"

/*Definitions*/
#define SPEED 340

#define TRIG_PORT_ID PORTB_ID
#define TRIG_PIN_ID PIN5_ID

#define ECHO_PORT_ID PORTD_ID
#define ECHO_PIN_ID PIN6_ID

/*Type Declarations*/

/*Functions Prototypes*/
void Ultrasonic_init(void);

void Ultrasonic_trigger(void);

uint16 Ultrasonic_readDistance(void);

void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
