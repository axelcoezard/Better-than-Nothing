#include "Engine/CWindow.hpp"
#include "Engine/CDevice.hpp"
#include "Engine/CRenderer.hpp"
#include "Engine/CModel.hpp"
#include "Handlers/CInput.hpp"
#include "Scene/CScene.hpp"
#include "Scene/CCamera.hpp"

using namespace BetterThanNothing;

int main(void) {
	auto pWindow = new CWindow("better than nothing", WINDOW_WIDTH, WINDOW_HEIGHT);
	auto pDevice = new CDevice(pWindow);
	auto pRenderer = new CRenderer(pWindow, pDevice);

	pRenderer->LoadPipeline(
		"main",
		"/home/acoezard/lab/better-than-nothing/Assets/Shaders/vert.spv",
		"/home/acoezard/lab/better-than-nothing/Assets/Shaders/frag.spv");

	CScene* pScene = new CScene("world");

	auto pCamera = pScene->InitCamera(0.0, 0.0, 400.0, -90.0f, 0.0f);
	pCamera->SetPerspectiveProjection(glm::radians(90.0f), 0.1f, 1000000.0f);

	pScene->LoadModel(
		pRenderer,
		"/home/acoezard/lab/better-than-nothing/Assets/Models/42/42.obj",
		"/home/acoezard/lab/better-than-nothing/Assets/Models/42/metal.jpg");

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
	float frameTime = 1.0f / 60.0f;

	pRenderer->PrepareFrame(pScene);
	while (!pWindow->ShouldClose()) {
		pWindow->Poll();

		float currentFrame = glfwGetTime();
		deltatime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		pScene->Update(deltatime);
		pRenderer->Render(pScene);

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


