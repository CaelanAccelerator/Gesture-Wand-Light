#pragma once
#include "Status.hpp"
#include "MotionData.hpp"

class ISensor{
public:
	virtual ~ISensor() {}
	virtual Status read(MotionData& out) = 0;
	virtual Status init() = 0;
};
