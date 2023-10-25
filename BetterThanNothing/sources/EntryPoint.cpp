#include "Engine/Window.hpp"
#include "Engine/Device.hpp"
#include "Engine/Renderer.hpp"
#include "Engine/Model.hpp"
#include "Engine/DescriptorPool.hpp"
#include "Engine/SwapChain.hpp"
#include "Handlers/Input.hpp"
#include "Scene/Scene.hpp"
#include "Scene/Camera.hpp"

using namespace BetterThanNothing;

int main(void) {
	auto pWindow = new Window("better than nothing", WINDOW_WIDTH, WINDOW_HEIGHT);
	auto pDevice = new Device(pWindow);
	auto pRenderer = new Renderer(pWindow, pDevice);

	pRenderer->LoadPipeline(
		"main",
		"/home/acoezard/lab/better-than-nothing/Assets/Shaders/vert.spv",
		"/home/acoezard/lab/better-than-nothing/Assets/Shaders/frag.spv");

	Scene* pScene = new Scene("world");

	auto pCamera = pScene->InitCamera(0.0, 0.0, 400.0, 0.0f, 0.0f);
	pCamera->SetPerspectiveProjection(glm::radians(45.0f), 0.1f, 1000000.0f);

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

	float deltatime = 0.0f;
	float lastFrame = 0.0f;
	float frameTime = 1.0f / 240.0f;
	uint32_t frameCount = 0;

	pRenderer->Prepare(pScene);

	while (!pWindow->ShouldClose()) {
		pWindow->Poll();

		float currentFrame = glfwGetTime();
		deltatime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		frameCount += 1;

		pScene->Update(deltatime);

		if (pRenderer->BeginRender(pScene)) {

			pScene->Render(pRenderer);

			ImGui_ImplVulkan_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			if (ImGui::BeginMainMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					ImGui::MenuItem("Hello world", "bip bip");
					ImGui::EndMenu();
				}
				ImGui::EndMainMenuBar();
			}

			ImGui::Render();

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

	delete pScene;
	delete pRenderer;
	delete pDevice;
	delete pWindow;

	return EXIT_SUCCESS;
}


