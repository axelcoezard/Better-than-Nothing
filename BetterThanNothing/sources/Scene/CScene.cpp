#include "Engine/CDevice.hpp"
#include "Engine/CRenderer.hpp"
#include "Engine/CModel.hpp"
#include "Scene/CScene.hpp"
#include "Scene/CCamera.hpp"

namespace BetterThanNothing
{
	CScene::CScene(std::string_view name)
	{
		m_Name = name;
	}

	CScene::~CScene()
	{
		for (uint32_t i = 0; i < m_pModels.size(); i++) {
			delete m_pModels[i];
		}

		delete m_pCamera;
	}

	CCamera* CScene::InitCamera(double x, double y, double z, double yaw, double pitch)
	{
		m_pCamera = new CCamera(x, y, z, yaw, pitch);
		return m_pCamera;
	}

	void CScene::LoadModel(CRenderer* pRenderer, const std::string& modelPath, const std::string& texturePath)
	{
		auto model = new CModel(pRenderer->GetDevice(), pRenderer);
		model->LoadFromFiles(modelPath, texturePath);

		m_pModels.push_back(model);
	}

	void CScene::Update(float deltatime)
	{
		m_pCamera->Update(deltatime);

		m_pModels[0]->SetPosition(glm::vec3(10.0f, 0.0f, 0.0f));
		m_pModels[0]->SetRotation(glm::vec3(0.0f, 10.0f, 0.0f));
	}
};
