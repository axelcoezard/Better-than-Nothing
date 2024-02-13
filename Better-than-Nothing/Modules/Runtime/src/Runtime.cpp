#include "Runtime.hpp"

#include <BetterThanNothing.hpp>

namespace BetterThanNothing
{
	void Runtime::OnEnable()
	{
		m_ShaderPool->GetResource("main/main.vert");
		m_ShaderPool->GetResource("main/main.frag");

		m_ModelPool->GetResource("robot/robot.obj");
		m_TexturePool->GetResource("robot/robot.png");

		m_ModelPool->GetResource("42/42.obj");
		m_TexturePool->GetResource("42/42.jpg");

		m_Renderer->LoadPipeline("main", "main/main.vert", "main/main.frag");

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
	return new BetterThanNothing::Runtime();
}
