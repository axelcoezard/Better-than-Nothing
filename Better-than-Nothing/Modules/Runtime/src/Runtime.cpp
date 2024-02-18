#include "Runtime.hpp"

#include <BetterThanNothing.hpp>

namespace BetterThanNothing
{
	void Runtime::OnEnable()
	{
		m_ResourceManager->GetShader("main/main.vert");
		m_ResourceManager->GetShader("main/main.frag");

		m_ResourceManager->GetModel("robot/robot.obj");
		m_ResourceManager->GetTexture("robot/robot.png");

		m_ResourceManager->GetModel("42/42.obj");
		m_ResourceManager->GetTexture("42/42.jpg");

		m_Renderer->LoadPipeline("main", "main/main.vert", "main/main.frag");

		Scene* pScene = CreateScene("world");

		auto pCamera = pScene->InitCamera(0.0, 0.0, 200.0, 0.0f, 0.0f);
		pCamera->SetPerspectiveProjection(glm::radians(87.0f), 1.0f, 1000.0f);

		for (u32 i = 0; i < 10; i++)
		{
			pScene->CreateEntity("robot/robot.obj", "robot/robot.png");
		}
	}

	void Runtime::OnDisable()
	{

	}
};

BetterThanNothing::Application* CreateApplication()
{
	return new BetterThanNothing::Runtime();
}
