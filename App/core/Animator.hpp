#pragma once
#include"LedColor.hpp"
#include"Status.hpp"
#include"ILight.hpp"

class Animator{
public:
	Animator(ILight *light){
		this->light_ = light;
	}

	Status renderGradient(const LedColor &startColor, const LedColor &endColor){
		uint8_t r;
		uint8_t g;
		uint8_t b;

		int numPixels = light_->getNumPixels();
		if(numPixels <= 1){
			printf("Have less than 2 pixels, can not renderGradient\r\n");
			return Status::Err;
		}

		for(int i = 0; i < numPixels; i++){
			r = startColor.r + (endColor.r - startColor.r) * i / (numPixels - 1);
			g = startColor.g + (endColor.g - startColor.g) * i / (numPixels - 1);
			b = startColor.b + (endColor.b - startColor.b) * i / (numPixels - 1);
			light_-> setPixel(i, r, g, b);
		}


		return light_->show();
	}

private:
	ILight * light_;
};
