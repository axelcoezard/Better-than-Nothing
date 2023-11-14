#include "Runtime.hpp"

#include <BetterThanNothing.hpp>

namespace BetterThanNothing
{
	void Runtime::OnEnable()
	{
		m_pRenderer->LoadPipeline(
			"main",
			"/home/acoezard/lab/better-than-nothing/Better-than-Nothing/Shaders/vert.spv",
			"/home/acoezard/lab/better-than-nothing/Better-than-Nothing/Shaders/frag.spv");

		m_ModelPool->GetRessource("viking_room/viking_room.obj");
		m_ModelPool->GetRessource("robot/robot.obj");
		m_ModelPool->GetRessource("42/42.obj");

		Scene* pScene = CreateScene("world");

		auto pCamera = pScene->InitCamera(0.0, 0.0, 400.0, 0.0f, 0.0f);
		pCamera->SetPerspectiveProjection(glm::radians(45.0f), 0.1f, 1000000.0f);

	}

	void Runtime::OnDisable()
	{

	}
};

BetterThanNothing::Application* CreateApplication()
{
	return new BetterThanNothing::Runtime("better-than-nothing", WINDOW_WIDTH, WINDOW_HEIGHT);
}
