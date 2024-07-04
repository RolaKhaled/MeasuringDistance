#ifndef ICU_H_
#define ICU_H_

#include"std_types.h"

/*Definitions*/

/*Type Declarations*/
typedef enum{
	NO_CLOCK,F_CPU_1,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}ICU_ClkSelect;

typedef enum{
	FALLING,RISING
}ICU_EdgeSelect;

typedef struct{
	ICU_ClkSelect clk;
	ICU_EdgeSelect edge;
}ICU_Config;

/*Functions Prototypes*/
void ICU_init(const ICU_Config *config_ptr);

void ICU_setCallBack(void (*function_ptr)(void));

void ICU_setEdgeDetectionType(ICU_EdgeSelect edge);

uint16 ICU_getInputCaptureValue(void);

void ICU_clearTimerValue(void);

void ICU_deInit(void);

#endif /* ICU_H_ */
