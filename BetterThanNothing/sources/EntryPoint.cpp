
#include "Engine/CWindow.hpp"
#include "Engine/CDevice.hpp"
#include "Engine/CRenderer.hpp"

using namespace BetterThanNothing;

int main(void) {
	auto pWindow = new CWindow("better than nothing", 720, 720);
	auto pDevice = new CDevice(pWindow);
	auto pRenderer = new CRenderer(pWindow, pDevice);

	pRenderer->LoadPipeline(
		"main",
		"/home/acoezard/lab/better-than-nothing/Assets/Shaders/vert.spv",
		"/home/acoezard/lab/better-than-nothing/Assets/Shaders/frag.spv");

	pRenderer->LoadModel(
		"42",
		"/home/acoezard/lab/better-than-nothing/Assets/Models/42/42.obj",
		"/home/acoezard/lab/better-than-nothing/Assets/Models/42/metal.jpg");

	pRenderer->LoadModel(
		"viking_room",
		"/home/acoezard/lab/better-than-nothing/Assets/Models/viking_room/viking_room.obj",
		"/home/acoezard/lab/better-than-nothing/Assets/Models/viking_room/viking_room.png");

	pRenderer->PrepareFrame();
	while (!pWindow->ShouldClose()) {
		pWindow->Poll();
		pRenderer->DrawFrame();
	}

	pDevice->Idle();

	delete pRenderer;
	delete pDevice;
	delete pWindow;

	return EXIT_SUCCESS;
}


