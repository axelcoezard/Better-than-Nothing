#include "Renderer/Device.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/DrawStream.hpp"

#include "Ressources/RessourcePool.hpp"
#include "Ressources/Model.hpp"
#include "Ressources/Texture.hpp"

#include "Scene/Scene.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Entity.hpp"

#include "Events/Event.hpp"

#include "Handlers/Input.hpp"

namespace BetterThanNothing
{
	Scene::Scene(u32 id, std::string_view name, ModelPool* modelPool, TexturePool* texturePool)
	{
		m_Id = id;
		m_Name = name;
		m_ModelPool = modelPool;
		m_TexturePool = texturePool;
	}

	Scene::~Scene()
	{
		for (u32 i = 0; i < m_Entities.size(); i++) {
			delete m_Entities[i];
		}

		delete m_Camera;
	}

	Camera* Scene::InitCamera(f64 x, f64 y, f64 z, f64 yaw, f64 pitch)
	{
		m_Camera = new Camera(x, y, z, yaw, pitch);
		return m_Camera;
	}

	Entity* Scene::CreateEntity(const std::string& modelPath, const std::string& texturePath)
	{
		Entity* entity = new Entity();
		entity->UseModel(m_ModelPool->GetRessource(modelPath));
		entity->UseTexture(m_TexturePool->GetRessource(texturePath));
		m_PendingEntities.push(entity);
		return entity;
	}

	void Scene::OnUpdate(f32 deltatime)
	{
		static u32 frames = 0;
		if (frames / 60 > 1 && Input::IsKeyPressed(GLFW_KEY_0)) {
			Entity* newModel = CreateEntity("42/42.obj", "42/42.jpg");
			newModel->SetRotation(glm::vec3(30.0f * (f32) glfwGetTime()));
			frames = 0;
		}
		frames++;

		m_Camera->Update(deltatime);

		f32 speed = 1.5f;
		f32 rotation = glm::mod(speed * 30.0f * (f32) glfwGetTime() * 1.5f, 360.0f);

		if (m_Entities.size() > 0) {
			m_Entities[0]->SetPosition(glm::vec3(3.0f, 0.0f, 0.0f));
			m_Entities[0]->SetRotation(glm::vec3(0.0f, (f32) rotation, 0.0f));
		}
	}

	void Scene::OnEvent(Event* pEvent)
	{
		m_Camera->OnEvent(pEvent);
	}
};
