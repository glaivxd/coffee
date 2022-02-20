#include <thread>

#include "features.hpp"
#include "../sdk/engine/engine.hpp"
#include "../utility/process/process.hpp"
#include "../sdk/offsets.hpp"

void Features::chams(Color rgb, float brightness)
{
	const auto _this = static_cast<std::uintptr_t>(Engine::engine + Signatures::model_ambient_min - 0x2c);
	process.write<std::int32_t>(Engine::engine + Signatures::model_ambient_min, *reinterpret_cast<std::uintptr_t*>(&brightness) ^ _this);

	auto local = Engine::get_local_player();
	
	Color balance;
	balance.r = 25.f;
	balance.g = 25.f;
	balance.b = 25.f;

	Color color;
	color.r = 255.f;
	color.g = 0.f;
	color.b = 0.f;

	while (1)
	{
		if (Engine::in_game())
		{
			if (!local.self)
				local = Engine::get_local_player();

			// Cant just loop player entities because we need CPredictedViewModel :|
			for (int i = 1; i < 1337; i++)
			{
				auto entity = Engine::get_entity(i);

				// Balance viewmodel brightness, sadly you cannot change the glowing part of arms
				if (entity.type() == ClassID::CPredictedViewModel)
				{
					process.write<int>(entity.self + 0x70, 25);
					process.write<int>(entity.self + 0x71, 25);
					process.write<int>(entity.self + 0x72, 25);
				}
				
				// cum in my tummy baby then i took a shit moment ngl 
				/*
				if (entity.type() == ClassID::CChicken)
					process.write<Color>(entity.self + 0x70, color);*/

				//if (entity.team() != local.team())
				//	process.write<Color>(entity.self + 0x70, color);
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}
