#include <thread>

#include "features.hpp"
#include "../sdk/engine/engine.hpp"
#include "../utility/process/process.hpp"
#include "../sdk/offsets.hpp"

void Features::night(float brightness)
{
	while (1)
	{
		if (Engine::in_game())
		{
			for (int i = 64; i < 2048; i++)
			{
				auto entity = Engine::get_entity(i);

				if (entity.type() == ClassID::CEnvTonemapController)
				{
					process.write<bool>(entity.self + Netvars::m_bUseCustomAutoExposureMin, true);
					process.write<bool>(entity.self + Netvars::m_bUseCustomAutoExposureMax, true);

					process.write<float>(entity.self + Netvars::m_flCustomAutoExposureMin, brightness);
					process.write<float>(entity.self + Netvars::m_flCustomAutoExposureMax, brightness);
				}
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
}