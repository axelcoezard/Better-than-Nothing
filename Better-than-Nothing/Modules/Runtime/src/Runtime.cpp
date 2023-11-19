#include "Runtime.hpp"

#include <BetterThanNothing.hpp>

namespace BetterThanNothing
{
	void Runtime::OnEnable()
	{
		m_pRenderer->LoadPipeline("main", "main/main.vert.spv", "main/main.frag.spv");

		m_ModelPool->GetRessource("viking_room/viking_room.obj");
		m_TexturePool->GetRessource("viking_room/viking_room.png");

		m_ModelPool->GetRessource("robot/robot.obj");
		m_TexturePool->GetRessource("robot/robot.png");

		m_ModelPool->GetRessource("42/42.obj");
		m_TexturePool->GetRessource("42/42.jpg");

		Scene* pScene = CreateScene("world");

		auto pCamera = pScene->InitCamera(0.0, 0.0, 400.0, 0.0f, 0.0f);
		pCamera->SetPerspectiveProjection(glm::radians(45.0f), 0.01f, 10000.0f);

		pScene->CreateEntity("viking_room/viking_room.obj", "viking_room/viking_room.png");
	}

	void Runtime::OnDisable()
	{

	}
};

BetterThanNothing::Application* CreateApplication()
{
	return new BetterThanNothing::Runtime("better-than-nothing", WINDOW_WIDTH, WINDOW_HEIGHT);
}
