#pragma once

#include"core/Gesture.hpp"

class ISender{
public:
	virtual ~ISender() {}

	virtual Status send(const Gesture g) = 0;

};
