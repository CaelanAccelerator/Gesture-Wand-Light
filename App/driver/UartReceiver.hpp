#pragma once

#include"core/IReciever.hpp"
#include "main.h"
#include <cstdint>

extern volatile bool g_uartReady;
extern volatile uint8_t g_uartByte;
extern uint8_t g_uartRxBuf;
extern UART_HandleTypeDef huart2;

class UartReceiver: public IReceiver{
public:
	void start(){
		HAL_UART_Receive_IT(&huart2, &g_uartRxBuf, 1);
	}

	bool receive(Gesture& out) override {
		if(!g_uartReady)
			return false;
		g_uartReady = false;
		out = (Gesture) g_uartByte;
		return true;
	}
};
