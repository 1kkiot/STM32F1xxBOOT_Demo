/* Includes ------------------------------------------------------------------*/

#include "stm32f1xx_hal.h"  
#include "Sys.h"
#include "gpio.h"
#include "uart.h"
#include "adc.h"
#include "Ranging.h"
#include "updata.h"
#include "queue.h"

int main(void)
{
	//Jump_IAP_APP();
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_USART1_UART_Init();
//	MX_TIM3_Init();
//	queue_test();
	while(1)
	{
		test_print();
	}
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
