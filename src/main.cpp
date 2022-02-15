#include <Windows.h>
#include <iostream>
#include <thread>

#include "sdk/engine/engine.hpp"
#include "features/features.hpp"

int main()
{
	SetConsoleTitleA("coffee [DEBUG]");
	std::cout << "Initializing" << std::endl;

	if (!Engine::initialize())
		std::cout << "Failed to initialize" << std::endl;

	std::cout << "Initialized" << std::endl;

	std::thread chams_thread(Features::chams);
	
	chams_thread.detach();

	// exit key
	while (!GetAsyncKeyState(VK_F1))
		Sleep(1000);

	return 0;
}