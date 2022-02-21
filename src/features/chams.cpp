#include <thread>

#include "features.hpp"
#include "../sdk/engine/engine.hpp"
#include "../utility/process/process.hpp"
#include "../sdk/offsets.hpp"

void Features::chams(ClrRender color, float brightness)
{
	ClrRender balance;
	balance.r = 255 / 10;
	balance.g = 255 / 10;
	balance.b = 255 / 10;
	
	auto local = Engine::get_local_player();

	// set model_ambient_min cvar
	const auto _this = static_cast<std::uintptr_t>(Engine::engine + Signatures::model_ambient_min - 0x2c);
	process.write<std::int32_t>(Engine::engine + Signatures::model_ambient_min, *reinterpret_cast<std::uintptr_t*>(&brightness) ^ _this);
	
	while (1)
	{
		if (Engine::in_game())
		{
			if (!local.self)
				local = Engine::get_local_player();

			// can also use cpredictedviewmodel classid
			auto viewmodel_entity = process.read<std::uint32_t>(Engine::client + Signatures::dwEntityList + ((process.read<std::uint32_t>(local.self + Netvars::m_hViewModel) & 0xFFF) - 1) * 16);
			process.write<ClrRender>(viewmodel_entity + Netvars::m_clrRender, balance);

			for (int i = 1; i < Engine::max_players(); i++)
			{
				auto entity = Engine::get_entity(i);

				if (entity.team() != local.team())
					process.write<ClrRender>(entity.self + Netvars::m_clrRender, color);
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
