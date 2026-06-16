#pragma once

#include"core/Gesture.hpp"

class IReceiver{
public:
	virtual ~IReceiver() {}

	virtual bool receive(Gesture& out) = 0;
};
