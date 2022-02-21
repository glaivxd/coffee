#include "engine.hpp"
#include "../../utility/process/process.hpp"
#include "../offsets.hpp"
#include "../enums.hpp"

bool Engine::initialize()
{
	while (!process.attach(L"csgo.exe"))
		Sleep(1000);

	while (!client)
	{
		client = process.get_module(L"client.dll");
		engine = process.get_module(L"engine.dll");
	}

	client_state = process.read<uint32_t>(engine + Signatures::dwClientState);

	return true;
}

bool Engine::in_game()
{
	if (process.read<SignOnState>(client_state + Signatures::dwClientState_State) != SignOnState::IN_GAME)
		return false;

	return true;
}

int Engine::max_players()
{
	return process.read<int>(client_state + Signatures::dwClientState_MaxPlayer);
}

Entity Engine::get_entity(uint32_t index)
{
	return process.read<Entity>(client + Signatures::dwEntityList + index * 0x10);
}

Entity Engine::get_local_player()
{
	return process.read<Entity>(client + Signatures::dwLocalPlayer);
}