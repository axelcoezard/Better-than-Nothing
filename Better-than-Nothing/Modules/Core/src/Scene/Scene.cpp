#include "Renderer/Device.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Model.hpp"
#include "Scene/Scene.hpp"
#include "Scene/Camera.hpp"
#include "Events/Event.hpp"

namespace BetterThanNothing
{
	Scene::Scene(std::string_view name)
	{
		m_Name = name;
	}

	Scene::~Scene()
	{
		for (uint32_t i = 0; i < m_pModels.size(); i++) {
			delete m_pModels[i];
		}

		delete m_pCamera;
	}

	Camera* Scene::InitCamera(double x, double y, double z, double yaw, double pitch)
	{
		m_pCamera = new Camera(x, y, z, yaw, pitch);
		return m_pCamera;
	}

	void Scene::LoadModel(Renderer* pRenderer, const std::string& modelPath, const std::string& texturePath)
	{
		auto model = new Model(pRenderer->GetDevice(), pRenderer);
		model->LoadFromFiles(modelPath, texturePath);

		m_pModels.push_back(model);
	}

	void Scene::Update(float deltatime)
	{
		m_pCamera->Update(deltatime);

		float rotation = glm::mod(30.0f * (float) glfwGetTime(), 360.0f);

		m_pModels[0]->SetPosition(glm::vec3(3.0f, 0.0f, 0.0f));
		m_pModels[0]->SetRotation(glm::vec3(0.0f, (float) rotation, 0.0f));

		m_pModels[1]->SetRotation(glm::vec3((float) rotation, 0.0f, 0.0f));
	}

	void Scene::Render(Renderer* pRenderer)
	{
		for (uint32_t i = 0; i < m_pModels.size(); i++) {
			pRenderer->DrawModel(m_pModels[i], i);
		}
	}

	void Scene::OnEvent(Event* pEvent)
	{
		m_pCamera->OnEvent(pEvent);
	}
};
