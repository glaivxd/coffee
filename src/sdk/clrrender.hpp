#pragma once

class ClrRender
{
public:
	unsigned char r, g, b;
};

namespace Colors
{
	inline ClrRender green = { 0, 255, 0 };
}