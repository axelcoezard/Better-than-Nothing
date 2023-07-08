
#include "Engine/CWindow.hpp"
#include "Engine/CDevice.hpp"

using namespace BetterThanNothing;

int main(void) {
	auto pWindow = std::make_unique<CWindow>("better than nothing", 720, 720);
	auto pDevice = std::make_unique<CDevice>(pWindow->GetPointer());

	pWindow->Open();

	while (!pWindow->ShouldClose()) {
		pWindow->Poll();
		// Update, clear and render
	}

	return EXIT_SUCCESS;
}


