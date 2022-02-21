#pragma once

class ClrRender
{
public:
	ClrRender(unsigned char red, unsigned char green, unsigned char blue)
	{
		r = red;
		g = green;
		b = blue;
	}

	// extravagant balls
	ClrRender() {};

	unsigned char r, g, b;
};

namespace Colors
{
	inline ClrRender green = { 0, 255, 0 };
}