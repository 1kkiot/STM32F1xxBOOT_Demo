#ifndef _uart_h
#define _uart_h

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "Sys.h"
#include "arm_base_define.h"

#define RX_LEN		1024

#pragma pack(push,1)
typedef struct
{
	u8 flag;
	u8 RX_pData[RX_LEN];
	u16 RX_Size;
}Uart_t;  
#pragma pack(pop)

typedef enum{
	UART_RX_STATE_READY,
	UART_RX_STATE_START
}_uartRxState;

extern Uart_t Uart1;

void MX_USART1_UART_Init(void);
void uart1_restart(void);

//extern UART_HandleTypeDef huart1;



#ifdef __cplusplus
}
#endif

#endif

