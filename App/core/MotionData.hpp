#pragma once

#include<cstdint>

struct MotionData{
	MotionData(int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz) :ax(ax), ay(ay),az(az),gx(gx),gy(gy),gz(gz)
	{}
	void reset(int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz){
		this->ax = ax;
		this->ay = ay;
		this->az = az;
		this->gx = gx;
		this->gy = gy;
		this->gz = gz;
	}

	int16_t ax, ay, az;
	int16_t gx, gy, gz;
};


const MotionData fake_swing = { 18000, 200, 1000, 50, 30, 20 };

const MotionData fake_idle = { 100, 50, 16000, 10, 5, 8 };

const MotionData fake_circle = { 2000, 1500, 16000, 12000, 800, 600 };
