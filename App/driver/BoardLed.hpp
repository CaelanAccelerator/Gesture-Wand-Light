#pragma once

#include <cstdio>
#include"../core/ILight.hpp"
#include"../core/Status.hpp"

class BoardLed : public ILight{
public:
	Status setColor(uint8_t r, uint8_t g, uint8_t b) override {
		printf("set color: red %d, green %d, blue %d \r\n", r, g, b);
		return Status::OK;
	}

	Status setBrightness(uint8_t b) override {
		printf("set brightness to: %d \r\n", b);
		return Status::OK;
	}

	Status update() override {
		printf("update one tick\r\n");
		return Status::OK;
	}

	Status on() override {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		printf("LED2 on\r\n");
		return Status::OK;
	}

	Status off() override {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		printf("LED2 off\r\n");
		return Status::OK;
	}
};
