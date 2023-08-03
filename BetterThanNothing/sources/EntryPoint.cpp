
#include "Engine/CWindow.hpp"
#include "Engine/CDevice.hpp"
#include "Engine/CRenderer.hpp"

using namespace BetterThanNothing;

int main(void) {
	auto pWindow = new CWindow("better than nothing", 720, 720);
	auto pDevice = new CDevice(pWindow);
	auto pRenderer = new CRenderer(pWindow, pDevice);

	while (!pWindow->ShouldClose()) {
		pWindow->Poll();
		pRenderer->DrawFrame();
	}

	pDevice->Idle();

	delete pDevice;
	delete pWindow;

	return EXIT_SUCCESS;
}


