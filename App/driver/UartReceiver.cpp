#include "UartReceiver.hpp"

volatile bool g_uartReady = false;
volatile uint8_t g_uartByte = 0;
uint8_t g_uartRxBuf = 0;

extern "C" void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART2){
		g_uartByte = g_uartRxBuf;
		g_uartReady = true;
		//Restart Receiving
		HAL_UART_Receive_IT(huart, &g_uartRxBuf, 1);

	}
}
