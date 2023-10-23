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

	ImGui::CreateContext();
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui_ImplGlfw_InitForVulkan(pWindow->GetPointer(), true);

	ImGui_ImplVulkan_InitInfo info = {};
	info.Instance = pDevice->GetVkInstance();
	info.PhysicalDevice = pDevice->GetVkPhysicalDevice();
	info.Device = pDevice->GetVkDevice();
	info.DescriptorPool = pRenderer->GetDescriptorPool()->GetVkDescriptorPool();
	info.ImageCount = MAX_FRAMES_IN_FLIGHT;
	info.MinImageCount = 2;
	info.MSAASamples = pDevice->GetMsaaSamples();
	info.Queue = pDevice->GetVkGraphicsQueue();

	ImGui_ImplVulkan_Init(&info, pRenderer->GetSwapChain()->GetVkRenderPass());

	VkCommandBuffer commandBuffer = pRenderer->GetSwapChain()->BeginSingleTimeCommands();
	ImGui_ImplVulkan_CreateFontsTexture(commandBuffer);
	pRenderer->GetSwapChain()->EndSingleTimeCommands(commandBuffer);

	vkDeviceWaitIdle(pDevice->GetVkDevice());
	ImGui_ImplVulkan_DestroyFontUploadObjects();


	while (!pWindow->ShouldClose()) {
		pWindow->Poll();

		float currentFrame = glfwGetTime();
		deltatime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		frameCount += 1;

		pScene->Update(deltatime);
		pRenderer->Render(pScene);

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

	ImGui_ImplVulkan_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	delete pScene;
	delete pRenderer;
	delete pDevice;
	delete pWindow;

	return EXIT_SUCCESS;
}


