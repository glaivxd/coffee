#pragma once

#include <cstdint>

#include "../enums.hpp"
#include "../clrrender.hpp"

class Entity
{
public:
	uint32_t self;

	bool valid();
	int health();
	ClassID type();
	int team();
	int flags();

	void glow();
};