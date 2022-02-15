#include <thread>

#include "features.hpp"
#include "../sdk/engine/engine.hpp"
#include "../utility/process/process.hpp"

void Features::chams()
{
	while (1)
	{
		if (Engine::in_game)
		{
			for (int i = 1; i < Engine::max_players(); i++)
			{
				auto entity = Engine::get_entity(i);

				if (entity.valid())
				{
					process.write<int>(entity.self + 0x70, 0);
					process.write<int>(entity.self + 0x71, 255);
					process.write<int>(entity.self + 0x72, 0);
				}
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}