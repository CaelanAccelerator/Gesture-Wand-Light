#pragma once

#include "ILight.hpp"
#include "Gesture.hpp"

class LightController{
public:
	LightController(ILight *light) : light_(light) {}

	void handleGesture(Gesture g){
		switch (g){
		case Gesture::None:
			light_->off();
			break;
		case Gesture::Swing:
			light_->on();
			break;
		case Gesture::Circle:
			light_->setBrightness(123);
			break;
		}
	}
private:
	ILight *light_;
};
