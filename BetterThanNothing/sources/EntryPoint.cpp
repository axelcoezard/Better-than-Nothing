
#include "Engine/CWindow.hpp"
#include "Engine/CDevice.hpp"
#include "Engine/CCommandPool.hpp"
#include "Engine/CSwapChain.hpp"
#include "Engine/CDescriptorPool.hpp"
#include "Engine/CPipeline.hpp"

using namespace BetterThanNothing;

int main(void) {
	auto pWindow = new CWindow("better than nothing", 720, 720);
	pWindow->Open();

	// unique instances
	auto pDevice = new CDevice(pWindow);
	auto pCommandPool = new CCommandPool(pDevice);
	auto pSwapChain = new CSwapChain(pWindow, pDevice, pCommandPool);
	auto pDescriptorPool = new CDescriptorPool(pDevice, pSwapChain);

	// one per shaders couple
	auto pPipeLine = new CPipeline(pDevice, pSwapChain, pDescriptorPool);

	while (!pWindow->ShouldClose()) {
		pWindow->Poll();
		pSwapChain->DrawFrame(pDescriptorPool, pPipeLine);
		// Update, clear and render
	}

	vkDeviceWaitIdle(pDevice->GetVkDevice());

	delete pPipeLine;
	delete pDescriptorPool;
	delete pSwapChain;
	delete pCommandPool;
	delete pDevice;
	delete pWindow;

	return EXIT_SUCCESS;
}


