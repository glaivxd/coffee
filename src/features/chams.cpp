#include <thread>

#include "features.hpp"
#include "../sdk/engine/engine.hpp"
#include "../utility/process/process.hpp"
#include "../sdk/offsets.hpp"

// this is so spaghetti aaaaaaaaa
void Features::chams(Color rgb, float brightness, bool health_based)
{
	// write a cvar class af
	const auto _this = static_cast<std::uintptr_t>(Engine::engine + Signatures::model_ambient_min - 0x2c);
	process.write<std::int32_t>(Engine::engine + Signatures::model_ambient_min, *reinterpret_cast<std::uintptr_t*>(&brightness) ^ _this);
	auto local = Engine::get_local_player();

	struct ClRender {
		float r;
		float g;
		float b;
	};

	ClRender balance;
	balance.r = 25;
	balance.g = 25;
	balance.b = 25;

	ClRender color;
	color.r = rgb.r;
	color.g = rgb.g;
	color.b = rgb.b;

	while (1)
	{
		if (Engine::in_game())
		{
			if (!local.valid())
				local = Engine::get_local_player();

			// Cant just loop player entities because we need CPredictedViewModel :|
			for (int i = 1; i < 1337; i++)
			{
				auto entity = Engine::get_entity(i);

				// Balance viewmodel brightness, sadly you cannot change the glowing part of arms
				if (entity.type() == ClassID::CPredictedViewModel)
					process.write<ClRender>(entity.self + 0x70, balance);

				// :)
				if (entity.type() == ClassID::CChicken)
					process.write<ClRender>(entity.self + 0x70, color);

				// worlds a fuck
				if (entity.valid())
				{
					if (entity.team() != local.team())
					{
						if (health_based)
						{
							auto hp = entity.health();

							process.write<int>(entity.self + 0x70, 255 - 2.55 * hp) / 255.0f;
							process.write<int>(entity.self + 0x71, 2.55 * hp) / 255.0f;
							process.write<int>(entity.self + 0x72, 0);
						}
						
						else
						{
							process.write<int>(entity.self + 0x70, rgb.r);
							process.write<int>(entity.self + 0x71, rgb.g);
							process.write<int>(entity.self + 0x72, rgb.b);
						}
					}
				}
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}
