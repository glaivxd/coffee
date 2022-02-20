#pragma once

#include <cstdint>

#include "../class_id.hpp"

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