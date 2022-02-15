#pragma once

// color class !
class Color
{
public:
	Color(float red, float green, float blue)
	{
		r = red;
		g = green;
		b = blue;
	}

	float r;
	float g;
	float b;
};

inline Color red = { 255, 0, 0 };