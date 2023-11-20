#include "Runtime.hpp"

#include <BetterThanNothing.hpp>

namespace BetterThanNothing
{
	void Runtime::OnEnable()
	{
		m_ModelPool->GetRessource("robot/robot.obj");
		m_TexturePool->GetRessource("robot/robot.png");

		m_ModelPool->GetRessource("42/42.obj");
		m_TexturePool->GetRessource("42/42.jpg");

		Scene* pScene = CreateScene("world");

		auto pCamera = pScene->InitCamera(0.0, 0.0, 200.0, 0.0f, 0.0f);
		pCamera->SetPerspectiveProjection(glm::radians(87.0f), 1.0f, 1000.0f);

		pScene->CreateEntity("robot/robot.obj", "robot/robot.png");
	}

	void Runtime::OnDisable()
	{

	}
};

BetterThanNothing::Application* CreateApplication()
{
	return new BetterThanNothing::Runtime("better-than-nothing", WINDOW_WIDTH, WINDOW_HEIGHT);
}
