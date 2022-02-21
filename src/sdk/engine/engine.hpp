#pragma once

#include "../entity/entity.hpp"

namespace Engine
{
	// initialize a bunch of things needed for hack to run
	bool initialize();

	bool in_game();

	int max_players();
	Entity get_entity(uint32_t index);
	Entity get_local_player();

	// modules
	inline uint32_t client;
	inline uint32_t engine;

	// take a look at the goop
	inline uint32_t client_state;
}