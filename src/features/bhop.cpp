#include <thread>

#include "features.hpp"
#include "../sdk/engine/engine.hpp"
#include "../utility/process/process.hpp"
#include "../sdk/offsets.hpp"


void Features::bhop()
{
	auto local = Engine::get_local_player();

	while (1)
	{
		if (Engine::in_game())
		{
			if (!local.self)
				local = Engine::get_local_player();

			if (GetAsyncKeyState(VK_SPACE))
			{
				if (local.flags() & 1)
					process.write<int>(Engine::client + Signatures::dwForceJump, 6);
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(6));
	}
}