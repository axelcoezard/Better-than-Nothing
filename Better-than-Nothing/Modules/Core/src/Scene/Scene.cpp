#include "Renderer/Device.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Model.hpp"
#include "Renderer/DrawStream.hpp"
#include "Scene/Scene.hpp"
#include "Scene/Camera.hpp"
#include "Events/Event.hpp"

namespace BetterThanNothing
{
	Scene::Scene(u32 id, std::string_view name)
	{
		m_Id = id;
		m_Name = name;
	}

	Scene::~Scene()
	{
		for (u32 i = 0; i < m_pModels.size(); i++) {
			delete m_pModels[i];
		}

		delete m_pCamera;
	}

	Camera* Scene::InitCamera(f64 x, f64 y, f64 z, f64 yaw, f64 pitch)
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

	void Scene::OnUpdate(f32 deltatime)
	{
		m_pCamera->Update(deltatime);

		f32 rotation = glm::mod(30.0f * (f32) glfwGetTime(), 360.0f);

		m_pModels[0]->SetPosition(glm::vec3(3.0f, 0.0f, 0.0f));
		m_pModels[0]->SetRotation(glm::vec3(0.0f, (f32) rotation, 0.0f));

		m_pModels[1]->SetRotation(glm::vec3((f32) rotation, 0.0f, 0.0f));
	}

	void Scene::OnEvent(Event* pEvent)
	{
		m_pCamera->OnEvent(pEvent);
	}
};
