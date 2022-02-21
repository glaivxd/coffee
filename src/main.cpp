#include <Windows.h>
#include <iostream>
#include <thread>

#include "sdk/engine/engine.hpp"
#include "features/features.hpp"

int main()
{
	SetConsoleTitleA("Coffee");
	std::cout << "Initializing" << std::endl;

	if (!Engine::initialize())
		std::cout << "Failed to initialize" << std::endl;

	std::thread chams_thread(Features::chams, 100);
	std::thread night_thread(Features::night, 0.75f);
	std::thread bhop_thread(Features::bhop);
	
	chams_thread.detach();
	night_thread.detach();
	bhop_thread.detach();

	std::cout << "Initialized" << std::endl;

	// exit key
	while (!GetAsyncKeyState(VK_F1))
		Sleep(1000);

	return 0;
}