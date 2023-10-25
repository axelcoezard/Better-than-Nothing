#include "Application.hpp"

using namespace BetterThanNothing;

extern Application* CreateApplication(void);

int main() {
	Application* pApplication = CreateApplication();
	pApplication->Run();
	delete pApplication;

	return EXIT_SUCCESS;
}

/*auto pWindow = new Window("better than nothing", WINDOW_WIDTH, WINDOW_HEIGHT);
	auto pDevice = new Device(pWindow);
	auto pRenderer = new Renderer(pWindow, pDevice);

	pRenderer->LoadPipeline(
		"main",
		"/home/acoezard/lab/better-than-nothing/Assets/Shaders/vert.spv",
		"/home/acoezard/lab/better-than-nothing/Assets/Shaders/frag.spv");

	Scene* pScene = new Scene("world");

	pScene->LoadModel(
		pRenderer,
		"/home/acoezard/lab/better-than-nothing/Assets/Models/42/42.obj",
		"/home/acoezard/lab/better-than-nothing/Assets/Models/42/42.jpg");

	pScene->LoadModel(
		pRenderer,
		"/home/acoezard/lab/better-than-nothing/Assets/Models/viking_room/viking_room.obj",
		"/home/acoezard/lab/better-than-nothing/Assets/Models/viking_room/viking_room.png");

	pScene->LoadModel(
		pRenderer,
		"/home/acoezard/lab/better-than-nothing/Assets/Models/robot/robot.obj",
		"/home/acoezard/lab/better-than-nothing/Assets/Models/robot/robot.png");


	pRenderer->Prepare(pScene);

	auto layerStack = LayerStack();
	layerStack.PushLayer(new ImGuiLayer());
	layerStack.PushLayer(new SceneLayer(pScene));

	float deltatime = 0.0f;
	float lastFrame = 0.0f;
	float frameTime = 1.0f / 240.0f;
	uint32_t frameCount = 0;

	layerStack.ForEach([](Layer* layer) { layer->OnAttach(); });
	while (!pWindow->ShouldClose()) {
		pWindow->Poll();

		float currentFrame = glfwGetTime();
		deltatime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		frameCount += 1;

		layerStack.ForEach([deltatime](Layer* layer) {
			layer->OnUpdate(deltatime);
		});

		if (pRenderer->BeginRender(pScene)) {

			layerStack.ForEach([pRenderer](Layer* layer) {
				layer->OnRender(pRenderer);
			});

			pRenderer->EndRender();
		}

		std::cout.precision(3);
		std::cout << "\033[2J\033[1;1H";
		std::cout << "Vendor: " << pDevice->GetVendorName() << std::endl;
		std::cout << "Device: " << pDevice->GetDeviceName() << std::endl;
		std::cout << "API version: " << pDevice->GetApiVersion() << std::endl;
		std::cout << "Frame time: " << deltatime * 1000 << "ms (" << (1.0f / deltatime) << " fps) " << std::endl;
		std::cout << "Frame count: " << frameCount << std::endl;

		useconds_t frameTimeMicroseconds = static_cast<useconds_t>(frameTime * 1000000);
		float elapsedTime = glfwGetTime() - currentFrame;
		if (elapsedTime < frameTime) {
			usleep(frameTimeMicroseconds - static_cast<useconds_t>(elapsedTime * 1000000));
		}
	}

	pDevice->Idle();

	layerStack.ForEach([](Layer* layer) { layer->OnDetach(); });

	delete pRenderer;
	delete pDevice;
	delete pWindow;*/


