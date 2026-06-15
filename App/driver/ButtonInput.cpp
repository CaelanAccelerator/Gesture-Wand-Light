#include "ButtonInput.hpp"
#include "main.h"
#include <stdio.h>

volatile bool g_button_pressed = false;

MotionData fake_swing = { 18000, 200, 1000, 50, 30, 20 };

MotionData fake_idle = { 100, 50, 16000, 10, 5, 8 };

MotionData fake_circle = { 2000, 1500, 16000, 12000, 800, 600 };


extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if (GPIO_Pin == B1_Pin){
		g_button_pressed = true;
		printf("INTERRUPT! button pressed\r\n");
	}
}

Status ButtonInput::read(MotionData &out){
	if(g_button_pressed == true){
		g_button_pressed = false;
		out = fake_swing;
	}else{
		out = fake_idle;
	}
	return Status::OK;
}
