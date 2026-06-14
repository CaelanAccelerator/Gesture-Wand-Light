#pragma once

#include<cstdint>

// Using POD for aggregate initialization
struct MotionData{
	int16_t ax = 0, ay = 0, az = 0;
	int16_t gx = 0, gy = 0, gz = 0;
};



