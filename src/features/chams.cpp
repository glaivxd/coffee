#include <thread>

#include "features.hpp"
#include "../sdk/engine/engine.hpp"
#include "../utility/process/process.hpp"

void Features::chams()
{
	auto model_ambient_min = 0x58F03C;

	int thisPtr = process.read<int>(Engine::engine + model_ambient_min - 0x2c);
	int xored = 1084227584 ^ thisPtr;
	process.write<int>(Engine::engine + model_ambient_min, xored);

	while (1)
	{
		if (Engine::in_game())
		{
			for (int i = 1; i < Engine::max_players(); i++)
			{
				auto entity = Engine::get_entity(i);
				auto local = Engine::get_local_player();

				if (entity.valid() && entity.team() != local.team())
				{
					auto hp = entity.health();

					process.write<int>(entity.self + 0x70, 255 - 2.55 * hp) / 255.0f;
					process.write<int>(entity.self + 0x71, 2.55 * hp ) / 255.0f;
					process.write<int>(entity.self + 0x72, 0);
				}
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}