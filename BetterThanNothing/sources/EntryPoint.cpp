#include "Application.hpp"

using namespace BetterThanNothing;

extern Application* CreateApplication(void);

int main() {
	Application* pApplication = CreateApplication();
	pApplication->Run();
	delete pApplication;

	return EXIT_SUCCESS;
}
