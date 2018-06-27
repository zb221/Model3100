
/* Includes ------------------------------------------------------------------*/
#define VARIABLE_GLOBALS
#include "main.h"
#include "stdio.h"
#include "peripheral.h"
#include "parament.h"
#include "AD7738.h"







void init_variables(void)
{
  normal_model = 0;
}

void init_peripherals(void)
{
	led_init();
	init_232();
	AD7738_CS_INIT();
	init_PWM();
  init_timer();
//	init_spi();
}

int main(void)
{
	int conter = 0;
  HAL_Init();
	
  SystemClock_Config();
	init_peripherals();
	init_variables();

	
  while (1)
  {
  	if (normal_model == 2){
			normal_model = 0;
			printf("Test OK,waitting......,conter=%d\r\n",conter++);
		}
	}


}





