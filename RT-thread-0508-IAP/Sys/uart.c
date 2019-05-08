#include "uart.h"

Uart_t Uart1;
_uartRxState uart1RxState=UART_RX_STATE_READY;

struct __FILE 
{
	int handle;
};
FILE __stdout;
void _sys_exit(int x)
{
	x = x; 
}
int fputc(int ch, FILE *f)
{
	while((USART1->SR&0X40)==0);
	USART1->DR = (uint8_t) ch;
	return ch;
}

//UART_HandleTypeDef huart1;
UART_HandleTypeDef UartHandle;
void MX_USART1_UART_Init(void)
{
	UartHandle.Instance = USART1;
	UartHandle.Init.BaudRate = 115200;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits = UART_STOPBITS_1;
	UartHandle.Init.Parity = UART_PARITY_NONE;
	UartHandle.Init.Mode = UART_MODE_TX_RX;
	UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&UartHandle) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	//__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
	
}

//void user_Uart1Handler()
//{
//	u8 temp=0;
//	if((__HAL_UART_GET_FLAG(&huart1,UART_FLAG_RXNE)!=RESET))
//	{
//		temp = (uint8_t)(huart1.Instance->DR);
//		if(uart1RxState == UART_RX_STATE_READY)
//		{
//			__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
//			uart1RxState = UART_RX_STATE_START;
//			Uart1.RX_Size = 0;
//			Uart1.RX_pData[Uart1.RX_Size++] = temp;
//		}
//		else if(uart1RxState == UART_RX_STATE_START) 
//		{
//			Uart1.RX_pData[Uart1.RX_Size++] = temp;
//		}
//		__HAL_UART_CLEAR_FLAG(&huart1,UART_FLAG_RXNE);
//	}
//	if((__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE)!=RESET))
//	{
//		//TogglePin(LED2);
//		Uart1.flag = true;
//		uart1RxState = UART_RX_STATE_READY;
//		__HAL_UART_DISABLE_IT(&huart1, UART_IT_IDLE);
//		__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
//	}
//}

void USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(&UartHandle);
	//user_Uart1Handler();
}


void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct;
	if(uartHandle->Instance==USART1)
	{
		/* USER CODE BEGIN USART1_MspInit 0 */

		/* USER CODE END USART1_MspInit 0 */
		/* USART1 clock enable */
		__HAL_RCC_USART1_CLK_ENABLE();

		/**USART1 GPIO Configuration    
		PA9     ------> USART1_TX
		PA10     ------> USART1_RX 
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_9;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USART1 interrupt Init */
		HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(USART1_IRQn);
		/* USER CODE BEGIN USART1_MspInit 1 */

		/* USER CODE END USART1_MspInit 1 */
	}
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

	if(uartHandle->Instance==USART1)
	{
		/* USER CODE BEGIN USART1_MspDeInit 0 */

		/* USER CODE END USART1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART1_CLK_DISABLE();

		/**USART1 GPIO Configuration    
		PA9     ------> USART1_TX
		PA10     ------> USART1_RX 
		*/
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

		/* USART1 interrupt Deinit */
		HAL_NVIC_DisableIRQ(USART1_IRQn);
		/* USER CODE BEGIN USART1_MspDeInit 1 */

		/* USER CODE END USART1_MspDeInit 1 */
	}
}


