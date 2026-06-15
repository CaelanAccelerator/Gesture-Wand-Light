#pragma once

#include "core/Status.hpp"
#include "core/ISensor.hpp"
#include "core/MotionData.hpp"

extern volatile bool g_button_pressed;

class ButtonInput: public ISensor{
public:
	Status init() override{return Status::OK;}

	Status read(MotionData& out) override;

};
