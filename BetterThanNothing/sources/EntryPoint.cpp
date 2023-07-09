
#include "Engine/CWindow.hpp"
#include "Engine/CDevice.hpp"
#include "Engine/CSwapChain.hpp"
#include "Engine/CCommandPool.hpp"
#include "Engine/CCommandBuffer.hpp"
#include "Engine/CPipeline.hpp"

using namespace BetterThanNothing;

int main(void) {
	auto pWindow = new CWindow("better than nothing", 720, 720);
	pWindow->Open();

	// unique instances
	auto pDevice = new CDevice(pWindow);
	auto pSwapChain = new CSwapChain(pWindow, pDevice);
	auto pCommandPool = new CCommandPool(pDevice);

	// one per shaders couple
	auto pPipeLine = new CPipeline(pDevice, pSwapChain);
	auto pCommandBuffer = new CCommandBuffer(pDevice, pSwapChain, pPipeLine, pCommandPool);

	while (!pWindow->ShouldClose()) {
		pWindow->Poll();
		pSwapChain->DrawFrame(pCommandBuffer);
		// Update, clear and render
	}

	vkDeviceWaitIdle(pDevice->GetVkDevice());

	delete pCommandBuffer;
	delete pPipeLine;
	delete pCommandPool;
	delete pSwapChain;
	delete pDevice;
	delete pWindow;

	return EXIT_SUCCESS;
}


