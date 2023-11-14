#include "Sandbox.hpp"

#include <BetterThanNothing.hpp>

namespace BetterThanNothing
{
	void Sandbox::OnEnable()
	{
		m_pRenderer->LoadPipeline(
			"main",
			"/home/acoezard/lab/better-than-nothing/Better-than-Nothing/Shaders/vert.spv",
			"/home/acoezard/lab/better-than-nothing/Better-than-Nothing/Shaders/frag.spv");

		Scene* pScene = CreateScene("world");

		auto pCamera = pScene->InitCamera(0.0, 0.0, 400.0, 0.0f, 0.0f);
		pCamera->SetPerspectiveProjection(glm::radians(45.0f), 0.1f, 1000000.0f);

		pScene->LoadModel(
			m_pRenderer,
			"/home/acoezard/lab/better-than-nothing/Assets/Models/42/42.obj",
			"/home/acoezard/lab/better-than-nothing/Assets/Models/42/42.jpg");

		pScene->LoadModel(
			m_pRenderer,
			"/home/acoezard/lab/better-than-nothing/Assets/Models/viking_room/viking_room.obj",
			"/home/acoezard/lab/better-than-nothing/Assets/Models/viking_room/viking_room.png");

		pScene->LoadModel(
			m_pRenderer,
			"/home/acoezard/lab/better-than-nothing/Assets/Models/robot/robot.obj",
			"/home/acoezard/lab/better-than-nothing/Assets/Models/robot/robot.png");

		m_pRenderer->Prepare(pScene);
	}

	void Sandbox::OnDisable()
	{

	}
};

BetterThanNothing::Application* CreateApplication()
{
	return new BetterThanNothing::Sandbox("better-than-nothing", WINDOW_WIDTH, WINDOW_HEIGHT);
}
