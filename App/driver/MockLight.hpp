#pragma once

#include <cstdio>
#include"../core/ILight.hpp"
#include"../core/Status.hpp"
#include"core/LedColor.hpp"
class MockLight : public ILight{
public:
	Status setPixel(int index, uint8_t r, uint8_t g, uint8_t b) override {
		if(index >= numPixels || index < 0){
			printf("index %d is out of the numPixels %d", index, numPixels);
			return Status::Err;
		}
		this->leds[index] = LedColor{r,g,b};
		//printf("set led %d color: red %d, green %d, blue %d \r\n",index, r, g, b);
		return Status::OK;
	}

	Status setBrightness(uint8_t b) override {
		this->brightness = b;
		printf("set brightness to: %d \r\n", b);
		return Status::OK;
	}

	int getNumPixels() override{
		return numPixels;
	}

	Status show() override {
		printf("light color updated:\r\n");
		printf("================================= \r\n");
		printf("light brightness: %d\r\n", this->brightness);
		for(int i = 0; i < numPixels; i++){
			printf("led %d color: red %d, green %d, blue %d \r\n",
					i,
					leds[i].r * brightness / 255,
					leds[i].g * brightness / 255,
					leds[i].b * brightness / 255);
		}
		return Status::OK;
	}

	Status on() override {
		printf("LED2 on\r\n");
		return Status::OK;
	}

	Status off() override {
		printf("LED2 off\r\n");
		return Status::OK;
	}

private:
	static const uint16_t numPixels = 16; //mocked
	LedColor leds[numPixels];
	uint8_t brightness = 255;
};
