#pragma once

#include "MotionData.hpp"
#include "Gesture.hpp"
#include <cstdlib>

class GestureDetector{
public:
	Gesture gestureDetect(const MotionData &md){
		if(abs(md.ax) > THRESHOLD || abs(md.ay) > THRESHOLD || abs(md.az - GRAVITY) > THRESHOLD){
			return Gesture:: Swing;
		}
		return Gesture::None;
	}

private:
	static constexpr int16_t THRESHOLD = 10000;
	static constexpr int16_t GRAVITY = 16000;
};
