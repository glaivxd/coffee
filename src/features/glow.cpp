#include <thread>

#include "features.hpp"
#include "../sdk/engine/engine.hpp"

void Features::glow(ClrRender color)
{
	auto local = Engine::get_local_player();

	while (1)
	{
		if (Engine::in_game())
		{
			if (!local.self)
				local = Engine::get_local_player();

			for (int i = 1; i < Engine::max_players(); i++)
			{
				auto entity = Engine::get_entity(i);

				if (entity.team() != local.team())
					entity.glow();
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(11));
	}
}
