#include "Sys.h"
#include "stm32f1xx.h"
#include "SysGpio.h"
#include "arm_base_define.h"
#include "uart.h"
#include "boot1.h"
#include "flash.h"

#include "flash_if.h"
#include "menu.h"
#include "ymodem.h"
#include "common.h"

void iap_fun()
{
	Main_Menu();
}

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_USART1_UART_Init();
	FLASH_If_Init();
	while(1)
	{
		iap_fun();
	}
}





