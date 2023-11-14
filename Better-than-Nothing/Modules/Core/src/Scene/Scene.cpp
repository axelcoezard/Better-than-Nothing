#include "Renderer/Device.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Model.hpp"
#include "Renderer/DrawStream.hpp"
#include "Scene/Scene.hpp"
#include "Scene/Camera.hpp"
#include "Events/Event.hpp"
#include "Handlers/Input.hpp"

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

	Model* Scene::LoadModel(const std::string& modelPath, const std::string& texturePath)
	{
		Model* model = new Model();
		model->LoadFromFiles(modelPath, texturePath);
		m_pModelsWaiting.push(model);
		return model;
	}

	void Scene::OnUpdate(f32 deltatime)
	{
		if (Input::IsKeyPressed(GLFW_KEY_0)) {
			Model* newModel = LoadModel(
				"/home/acoezard/lab/better-than-nothing/Assets/Models/42/42.obj",
				"/home/acoezard/lab/better-than-nothing/Assets/Models/42/42.jpg"
			);
			newModel->SetRotation(glm::vec3(30.0f * (f32) glfwGetTime()));
		}

		m_pCamera->Update(deltatime);

		f32 rotation = glm::mod(30.0f * (f32) glfwGetTime(), 360.0f);

		if (m_pModels.size() > 0) {
			m_pModels[0]->SetPosition(glm::vec3(3.0f, 0.0f, 0.0f));
			m_pModels[0]->SetRotation(glm::vec3(0.0f, (f32) rotation, 0.0f));

			m_pModels[1]->SetRotation(glm::vec3((f32) rotation, 0.0f, 0.0f));
		}
	}

	void Scene::OnEvent(Event* pEvent)
	{
		m_pCamera->OnEvent(pEvent);
	}
};
