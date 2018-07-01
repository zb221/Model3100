/***********************************************
@		Description: This file is about data of LPC2194 Peripherals.
@		Copyright: Hydrogen Sense(Suzhou)  Technology Co.,Ltd. All rights reserved.
@		Author: zhuobin.
@		Date: 2017/9/22.
***********************************************/

#include "main.h"
#include "peripheral.h"
#include "parament.h"


#define CNTLQ           0x11
#define CNTLS           0x13
#define DEL               0x7F
#define BACKSPACE   0x08
#define CR                0x0D
#define LF                 0x0A

/***********************************************************
Description: Global variable region.
Author: zhuobin
Date: 2017/10/10
***********************************************************/
unsigned int count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0, count6 = 0;

unsigned char rcv_buf[60] = {0};
unsigned char rcv_char[60] = {0};
volatile unsigned char rcv_new = 0;
unsigned int rcv_cnt = 0;
unsigned int rcv_char_cnt = 0;
unsigned char rcv_char_flag = 0;

TIM_HandleTypeDef    TimHandle;
/* SPI handler declaration */
SPI_HandleTypeDef SpiHandle;
SPI_HandleTypeDef SpiHandle2;
UART_HandleTypeDef   UartHandle;

static GPIO_InitTypeDef  GPIO_InitStruct;

TIM_HandleTypeDef    TimHandle_PWM;


/*---------------------------------SPI---------------------------------------*/

void init_spi(void)
{

  /* Set the SPI parameters */
  SpiHandle.Instance               = SPIx;
  SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  SpiHandle.Init.Direction         = SPI_DIRECTION_2LINES;
  SpiHandle.Init.CLKPhase          = SPI_PHASE_1EDGE;
  SpiHandle.Init.CLKPolarity       = SPI_POLARITY_LOW;
  SpiHandle.Init.DataSize          = SPI_DATASIZE_8BIT;
  SpiHandle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
  SpiHandle.Init.TIMode            = SPI_TIMODE_DISABLE;
  SpiHandle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
  SpiHandle.Init.CRCPolynomial     = 7;
  SpiHandle.Init.CRCLength         = SPI_CRC_LENGTH_8BIT;
  SpiHandle.Init.NSS               = SPI_NSS_SOFT;
  SpiHandle.Init.NSSPMode          = SPI_NSS_PULSE_DISABLE;

  SpiHandle.Init.Mode = SPI_MODE_MASTER;


  if(HAL_SPI_Init(&SpiHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
	/* Set the SPI parameters */
  SpiHandle2.Instance               = SPIx_2;
  SpiHandle2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  SpiHandle2.Init.Direction         = SPI_DIRECTION_2LINES;
  SpiHandle2.Init.CLKPhase          = SPI_PHASE_1EDGE;
  SpiHandle2.Init.CLKPolarity       = SPI_POLARITY_LOW;
  SpiHandle2.Init.DataSize          = SPI_DATASIZE_8BIT;
  SpiHandle2.Init.FirstBit          = SPI_FIRSTBIT_MSB;
  SpiHandle2.Init.TIMode            = SPI_TIMODE_DISABLE;
  SpiHandle2.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
  SpiHandle2.Init.CRCPolynomial     = 7;
  SpiHandle2.Init.CRCLength         = SPI_CRC_LENGTH_8BIT;
  SpiHandle2.Init.NSS               = SPI_NSS_SOFT;
  SpiHandle2.Init.NSSPMode          = SPI_NSS_PULSE_DISABLE;

  SpiHandle2.Init.Mode = SPI_MODE_MASTER;


  if(HAL_SPI_Init(&SpiHandle2) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}
/***********************************************************
Function: Initialize SPI 0 to send one char data.
Input: one char data
Output: slave return data
Author: zhuobin
Date: 2017/10/10
Description: SPI 0 can send max 16BIT data one time.
***********************************************************/
unsigned char SPI1_SendDate(unsigned char date)
{
	uint8_t tmp = 0;
	HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t*)&date, (uint8_t *)&tmp, 1, 5000);
	return tmp;
}

/***********************************************************
Function: Initialize SPI 1 to send one char data.
Input: one char data
Output: slave return data
Author: zhuobin
Date: 2017/10/10
Description: SPI 1 can send max 16BIT data one time.
***********************************************************/
unsigned char SPI2_SendDate(unsigned char date)
{
	uint8_t tmp = 0;
  HAL_SPI_TransmitReceive(&SpiHandle2, (uint8_t*)&date, (uint8_t *)&tmp, 1, 5000);
	return tmp;
}
/*-------------------------------------------------------------------------------*/



static void Timeout_Error_Handler(void)
{
}
void Error_Handler(void)
{
}
void DelayNS (unsigned int uiDly)
{
    unsigned int  i;
    
    for(; uiDly > 0; uiDly--){
        for(i = 0; i < 50000; i++);
    }
}

int fputc(int ch,FILE *f)
{
    HAL_UART_Transmit(&UartHandle,(uint8_t *)&ch,1,2);
}

int fgetc(FILE *f)
{
  uint8_t  ch;
  HAL_UART_Receive(&UartHandle,(uint8_t *)&ch,1,0xFFFF);
  return  ch;
}

void init_232(void)
{
  UartHandle.Instance        = USARTx;

  UartHandle.Init.BaudRate   = 9600;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits   = UART_STOPBITS_1;
  UartHandle.Init.Parity     = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode       = UART_MODE_TX_RX;
  UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT; 
  if(HAL_UART_DeInit(&UartHandle) != HAL_OK)
  {
    Error_Handler();
  }  
  if(HAL_UART_Init(&UartHandle) != HAL_OK)
  {
    Error_Handler();
  }
}

void led_init(void)
{
  /* Configure LEDs */
//  BSP_LED_Init(LED3);
//  BSP_LED_Init(LED4);
//  BSP_LED_Init(LED5);
//  BSP_LED_Init(LED6);
//  BSP_LED_Init(LED7);
//  BSP_LED_Init(LED8);
//  BSP_LED_Init(LED9);
//  BSP_LED_Init(LED10);
}
void init_gpio(GPIO_TypeDef  *GPIOx,uint16_t GPIO_Pin)
{
  /* -1- Enable GPIOE Clock (to be able to program the configuration registers) */
	if (GPIOx == GPIOE)
  __HAL_RCC_GPIOE_CLK_ENABLE();
	else 	if (GPIOx == GPIOB)
  __HAL_RCC_GPIOB_CLK_ENABLE();
	 	if (GPIOx == GPIOA)
  __HAL_RCC_GPIOA_CLK_ENABLE();
	

  /* -2- Configure PE.8 to PE.15 IOs in output push-pull mode to drive external LEDs */
  GPIO_InitStruct.Pin = GPIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  
  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
void GPIO_On(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  HAL_GPIO_WritePin(GPIOx,GPIO_Pin,GPIO_PIN_SET); 
}
void GPIO_Off(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  HAL_GPIO_WritePin(GPIOx,GPIO_Pin,GPIO_PIN_RESET);
}

void init_timer(void)
{  
	uint32_t uwPrescalerValue = 0;
  /* Compute the prescaler value to have TIM3 counter clock equal to 10 KHz */
  uwPrescalerValue = (uint32_t) (SystemCoreClock / 10000) - 1;
  
  /* Set TIMx instance */
  TimHandle.Instance = TIMx_4;

  TimHandle.Init.Period = 10000 - 1;
  TimHandle.Init.Prescaler = uwPrescalerValue;
  TimHandle.Init.ClockDivision = 0;
  TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	
	if(HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  /*##-2- Start the TIM Base generation in interrupt mode ####################*/
  /* Start Channel1 */
  if(HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }
}

void init_PWM (void) 
{
/* Private typedef -----------------------------------------------------------*/
#define  PERIOD_VALUE       (uint32_t)(200 - 1)  /* Period Value  */
#define  PULSE3_VALUE       (uint32_t)(PERIOD_VALUE/2)        /* Capture Compare 3 Value  */

TIM_OC_InitTypeDef sConfig;
uint32_t uhPrescalerValue = 0;
  /* Compute the prescaler value to have TIM3 counter clock equal to 24000000 Hz */
  uhPrescalerValue = (uint32_t)(SystemCoreClock / 24000000) - 1;
/*---------------------------------------------------------*/
	  /* Initialize TIMx peripheral as follows:
       + Prescaler = (SystemCoreClock / 24000000) - 1
       + Period = (665 - 1)
       + ClockDivision = 0
       + Counter direction = Up
  */
  TimHandle_PWM.Instance = TIMx;

  TimHandle_PWM.Init.Prescaler         = uhPrescalerValue;
  TimHandle_PWM.Init.Period            = PERIOD_VALUE;
  TimHandle_PWM.Init.ClockDivision     = 0;
  TimHandle_PWM.Init.CounterMode       = TIM_COUNTERMODE_UP;
  TimHandle_PWM.Init.RepetitionCounter = 0;
  TimHandle_PWM.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

  if (HAL_TIM_PWM_Init(&TimHandle_PWM) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /*##-2- Configure the PWM channels #########################################*/
  /* Common configuration for all channels */
  sConfig.OCMode       = TIM_OCMODE_PWM1;
  sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;
  sConfig.OCFastMode   = TIM_OCFAST_DISABLE;
  sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
  sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;

  sConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;

  /* Set the pulse value for channel 1 */

  /* Set the pulse value for channel 3 */
  sConfig.Pulse = PULSE3_VALUE;
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle_PWM, &sConfig, TIM_CHANNEL_3) != HAL_OK)
  {
    /* Configuration Error */
    Error_Handler();
  }


  /*##-3- Start PWM signals generation #######################################*/

  /* Start channel 3 */
  if (HAL_TIM_PWM_Start(&TimHandle_PWM, TIM_CHANNEL_3) != HAL_OK)
  {
    /* PWM generation Error */
    Error_Handler();
  }

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		normal_model++;
//	count1++;
//	count2++;
//	count3++;
//	count4++;
//	count5++;
//	count6++;
//	
//	Intermediate_Data.count7++;

//	switch (output_data.MODEL_TYPE){
//		case 2:	/*debug model*/
//		case 1:	/*normal model*/
//			switch (count1){
//				case 60000:	/* 1-4min capture 3min oil temp */
//				Intermediate_Data.flag1 = 1;
//				Intermediate_Data.Power_On = 1;
//				Intermediate_Data.Start_print_H2R = 1;
//				Intermediate_Data.wait_1min_oil = 0;
//				break;
//				
//				case 180000: /* wait 2min for 1-4min capture 3min oil temp */
//					Intermediate_Data.wait_1min_oil = 1;
//				break;

//				case 240000:	/* 4-1H4min set 50 temp, keep 1H  */
//				Intermediate_Data.flag1 = 2;
//        Intermediate_Data.wait_1min = 0;
//				break;
//				
//				case 840000: /* wait 10min for 4-1H4min set 50 temp, keep 1H */
//				Intermediate_Data.wait_1min = 1;
//				Intermediate_Data.unready_current = 1;
//				break;

//				case 3840000: /* 1H4min-1H7min stop heating, capture 3min oil temp */
//				Intermediate_Data.flag1 = 3;
//				Intermediate_Data.wait_1min_oil = 0;
//				break;
//				
//				case 3960000: /* wait 2min for 1H4min-1H7min stop heating, capture 3min oil temp */
//				Intermediate_Data.wait_1min_oil = 1;
//				break;

//				case 4020000: /* 1H7min-2H7min set 50 temp and keep 1H */
//				Intermediate_Data.flag1 = 4;
//        Intermediate_Data.wait_1min = 0;
//				break;
//				
//				case 4620000: /* wait 10min for 1H7min-2H7min set 50 temp and keep 1H */
//				Intermediate_Data.wait_1min = 1;
//				break;

//				case 7620000: /* 2H7min-2H10min stop heating and capture oil temp 3min */
//				Intermediate_Data.flag1 = 5;
//				Intermediate_Data.wait_1min_oil = 0;
//				break;
//				
//				case 7740000: /*wait 2min for 2H7min-2H10min stop heating and capture oil temp 3min */
//				Intermediate_Data.wait_1min_oil = 1;
//				break;

//				case 7800000: /* 2H10min-4H10min set 70 temp and keep 2H */
//				Intermediate_Data.flag1 = 6;
//				Intermediate_Data.wait_1min = 0;
//				break;
//				
//				case 8400000: /* wait 10min for 2H10min-4H10min set 70 temp and keep 2H */
//				Intermediate_Data.wait_1min = 1;
//				break;

//				case 15000000: /* 4H10min-4H40min set 50 temp and keep 0.5H */
//				Intermediate_Data.flag1 = 7;
//				Intermediate_Data.wait_1min = 0;
//				break;

//				case 16800000: /*wait 1min for 4H10min-4H13min stop heating and capture oil temp 3min */
//				count1 = 60000 - 1;
//				break;

//				default:
//				break;
//			}
//			break;
//			      
//		case 3:	/*calibrate model*/
//			if (Intermediate_Data.Start_print_calibrate_H2R == 1){
//				Intermediate_Data.count6++;
//				if (Intermediate_Data.count6 == 60000){
//					Intermediate_Data.Start_print_calibrate_H2R = 2;
//					Intermediate_Data.count6 = 0;
//				}
//			}
//			switch (count6){
//				case 60000:
//					Intermediate_Data.Power_On = 1;
//					break;
//				
//				case 120000:
//					Intermediate_Data.wait_1min_oil = 1;
//				break;
//				
//				case 180000:
//					Intermediate_Data.count7 = 1;
//				  count6 = 0;
//				break;
//					
//				default:
//				break;
//			}
//				break;
//		
//		case 4:	/*OilTemp model*/
//			count1 = 0;
//			Intermediate_Data.flag1 = 0;
//			Intermediate_Data.Start_print_H2R = 0;
//			break;

//		default:
//			break;
//	}
//	
//	switch (count2){
//		case 200://100ms
//		Intermediate_Data.flag2 = 1;
//		break;
//		
//		case 1000://1000ms
//		Intermediate_Data.flag2 = 2;
//		count2 = 0;
//		Runtimes++;
//		break;

//		default:
//		break;
//	}

//	switch (count3){
//		case 1800000:
//		Intermediate_Data.flag3 = 1; /* 30min FLASH */
//		count3 = 0;
//		break;

//		default:
//		break;
//	}
//	
//	switch (count4){
//		case 30000:
//		Intermediate_Data.flag4 = 1;
//		count4 = 0;
//		break;

//		default:
//		break;
//	}
//	
//	if (count5%3600000==0)
//		Intermediate_Data.flag5 = 1; /* calculating day*/
//	else if (count5%14400000==0)
//		Intermediate_Data.flag5 = 2; /* calculating week*/
//	else if (count5%86400000==0){
//		Intermediate_Data.flag5 = 3; /* calculating month*/
//	}
//	switch (count5){
//		case 1800000: /*30min*/
//		Intermediate_Data.Start_day = 1;   /* Start calculating the daily rate of change */
//		break;
//		
//		case 21600000: /*6H*/
//		Intermediate_Data.Start_week = 1;  /* Start calculating the week rate of change */
//		Intermediate_Data.Start_month = 1; /* Start calculating the month rate of change */
//		break;
//		
//		case 604800000: /*7*24H*/
//		count5 = 0;
//		break;

//		default:
//		break;
//	}
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            HSE PREDIV                     = 1
  *            PLLMUL                         = RCC_PLL_MUL9 (9)
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    Error_Handler();
  }
}
#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

