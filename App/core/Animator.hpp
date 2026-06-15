#pragma once
#include"LedColor.hpp"
#include"Status.hpp"
#include"ILight.hpp"
#include"Palette.hpp"

class Animator{
public:
	Animator(ILight *light){
		this->light_ = light;
	}


	Status renderPalette(const Palette &palette){
		int numPixel = light_->getNumPixels();
		return renderGradient(palette.c1, palette.c2, palette.c3, 0, numPixel/2, numPixel);
	}

	Status renderGradient(const LedColor &startColor, const LedColor &endColor, const int start, const int end){
		uint8_t r;
		uint8_t g;
		uint8_t b;

		int totalPixels = light_->getNumPixels();
		if(start < 0 || start >= totalPixels){
			printf("start %d is in not valid range: [0,%d) \r\n", start, totalPixels);
			return Status::Err;
		}
		if(end < 0 || end > totalPixels){
			printf("end %d is not in valid range: [0,%d] \r\n", end, totalPixels);
			return Status::Err;
		}
		int numPixels = end - start;

		if(numPixels < 1){
			printf("Have no pixels, can not renderGradient\r\n");
			return Status::Err;
		}

		if(numPixels == 1){
			r = startColor.r + (endColor.r - startColor.r) / 2;
			g = startColor.g + (endColor.g - startColor.g) / 2;
			b = startColor.b + (endColor.b - startColor.b) / 2;
			light_-> setPixel(start, r, g, b);
			return Status::OK;
		}

		for(int i = start; i < end; i++){
			int pos = i - start;
			r = startColor.r + (endColor.r - startColor.r) * pos / (numPixels - 1);
			g = startColor.g + (endColor.g - startColor.g) * pos / (numPixels - 1);
			b = startColor.b + (endColor.b - startColor.b) * pos / (numPixels - 1);
			light_-> setPixel(i, r, g, b);
		}


		return Status::OK;
	}

	Status renderGradient(const LedColor &startColor,
						  const LedColor &middleColor,
						  const LedColor &endColor,
						  const int start,
						  const int mid,
						  const int end){
			if(start >= mid || mid >= end){
				printf("invalid index");
				return Status::Err;
			}
			if(renderGradient(startColor, middleColor, start, mid) == Status::Err){
				return Status::Err;
			}
			if(renderGradient(middleColor, endColor, mid, end) == Status::Err){
				return Status::Err;
			}
			;
			return Status::OK;
		}

	Status show(){
		return light_->show();
	}

private:
	ILight * light_;
};
