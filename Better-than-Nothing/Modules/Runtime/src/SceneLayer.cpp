#include "SceneLayer.hpp"

namespace BetterThanNothing
{
	SceneLayer::SceneLayer(Scene* pScene)
		: Layer("SceneLayer"), m_pScene(pScene) {}

	void SceneLayer::OnAttach()
	{
		auto pCamera = m_pScene->InitCamera(0.0, 0.0, 400.0, 0.0f, 0.0f);
		pCamera->SetPerspectiveProjection(glm::radians(45.0f), 0.1f, 1000000.0f);
	}

	void SceneLayer::OnDetach(void)
	{
		delete m_pScene;
	}

	void SceneLayer::OnUpdate(f32 deltatime)
	{
		m_pScene->Update(deltatime);
	}

	void SceneLayer::OnRender(Renderer* pRenderer)
	{
		auto models = m_pScene->GetModels();
		for (size_t i = 0; i < models.size(); i++) {
			pRenderer->GetSwapChain()->UpdateUniformBuffer(m_pScene, models[i], i);
		}

		m_pScene->Render(pRenderer);
	}

	void SceneLayer::OnEvent(Event* pEvent)
	{
		m_pScene->OnEvent(pEvent);
	}
};
