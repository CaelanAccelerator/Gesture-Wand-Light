#pragma once

#include<cstdint>

enum class Status{
	OK,
	Err,
};


// Abstract output interface for "a light".
// Runtime polymorphism: LightController holds an ILight* and swaps concrete
// implementations (BoardLed now, Ws2812Light later) without changing its code.
// Methods are low-frequency (once per frame), so virtual dispatch overhead is
// negligible here. CRTP is reserved for hot paths like sensor drivers.
class ILight{
public:
	virtual ~ILight() {}

	virtual Status setColor(uint8_t r, uint8_t g, uint8_t b) = 0;

	virtual Status setBrightness(uint8_t b) = 0;

	virtual Status update() = 0;

	virtual Status on() = 0;

	virtual Status off() = 0;
};
