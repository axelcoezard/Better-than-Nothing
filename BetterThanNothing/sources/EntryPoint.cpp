
#include "Engine/CWindow.hpp"
#include "Engine/CDevice.hpp"
#include "Engine/CSwapChain.hpp"
#include "Engine/CCommandPool.hpp"
#include "Engine/CCommandBuffer.hpp"
#include "Engine/CPipeline.hpp"

using namespace BetterThanNothing;

int main(void) {
	auto pWindow = std::make_shared<CWindow>("better than nothing", 720, 720);
	pWindow->Open();

	auto pDevice = std::make_shared<CDevice>(pWindow);
	auto pSwapChain = std::make_shared<CSwapChain>(pWindow, pDevice);
	auto pPipeLine = std::make_shared<CPipeline>(pDevice, pSwapChain);
	auto pCommandPool = std::make_shared<CCommandPool>(pDevice);
	auto pCommandBuffer = std::make_shared<CCommandBuffer>(pDevice, pSwapChain, pPipeLine, pCommandPool);

	while (!pWindow->ShouldClose()) {
		pWindow->Poll();
		// Update, clear and render
	}

	return EXIT_SUCCESS;
}


