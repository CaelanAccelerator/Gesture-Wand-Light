#pragma once

#include "core/ISender.hpp"
#include "main.h"

extern UART_HandleTypeDef huart2;

class UartSender: public ISender{
public:
	Status send (const Gesture g) override {
		uint8_t byte = (uint8_t) g;
		if(HAL_UART_Transmit(&huart2, &byte, 1, HAL_MAX_DELAY) != HAL_OK){
			return Status::Err;
		}
		return Status::OK;
	}
};
