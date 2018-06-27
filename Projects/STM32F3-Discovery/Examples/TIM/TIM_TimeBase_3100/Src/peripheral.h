/* peripheral.h*/
#include "stdio.h"
#include "main.h"

int fputc(int ch,FILE *f);
int fgetc(FILE *f);

void SystemClock_Config(void);
void init_timer(void);

void Error_Handler(void);
void DelayNS(unsigned int uiDly);

void init_spi(void);
unsigned char SPI1_SendDate(unsigned char date);
unsigned char SPI2_SendDate(unsigned char date);

void led_init(void);
void init_gpio(GPIO_TypeDef  *GPIOx,uint16_t GPIO_Pin);
void GPIO_On(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_Off(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

void init_232(void);
void init_PWM (void);




