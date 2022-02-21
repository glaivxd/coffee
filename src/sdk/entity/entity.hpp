#pragma once

#include <cstdint>

#include "../enums.hpp"

class Entity
{
public:
	uint32_t self;

	bool valid();
	int health();
	ClassID type();
	int team();
	int flags();
};