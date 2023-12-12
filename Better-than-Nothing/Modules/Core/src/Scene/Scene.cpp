#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	Scene::Scene(u32 id, std::string_view name, Window* window, ModelPool* modelPool, TexturePool* texturePool)
	{
		m_Id = id;
		m_Name = name;
		m_Window = window;
		m_ModelPool = modelPool;
		m_TexturePool = texturePool;
	}

	Scene::~Scene()
	{
		delete m_Camera;
	}

	Camera* Scene::InitCamera(f64 x, f64 y, f64 z, f64 yaw, f64 pitch)
	{
		m_Camera = new Camera(CameraType::FirstPerson, x, y, z, yaw, pitch);
		return m_Camera;
	}

	void Scene::OnUpdate(f32 deltatime)
	{
		m_Camera->Update(m_Window, deltatime);

		f32 speed = 1.5f;
		f32 rotation = glm::mod(speed * 30.0f * (f32) glfwGetTime() * 1.5f, 360.0f);

		GetView<TransformComponent>().each([&](auto entity, TransformComponent& transform) {
			(void) entity;
			transform.rotation = glm::vec3(0.0f, (f32) rotation, 0.0f);
		});
	}

	void Scene::OnEvent(Event* pEvent)
	{
		m_Camera->OnEvent(pEvent);
	}

	u32 Scene::GetId()
	{
		return m_Id;
	}

	std::string& Scene::GetName()
	{
		return m_Name;
	}

	Camera* Scene::GetCamera()
	{
		return m_Camera;
	}

	Entity Scene::CreateEntity(const std::string& modelPath, const std::string& texturePath)
	{
		ModelComponent modelComponent;
		modelComponent.model = m_ModelPool->GetRessource(modelPath);
		modelComponent.texture = m_TexturePool->GetRessource(texturePath);

		TransformComponent transformComponent;
		transformComponent.position = glm::vec3(0.0f, 0.0f, 0.0f);
		transformComponent.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		transformComponent.scale = glm::vec3(1.0f, 1.0f, 1.0f);

		Entity entity = m_Registry.create();
		AddComponent<ModelComponent>(entity, modelComponent);
		AddComponent<TransformComponent>(entity, transformComponent);
		m_PendingEntities.push(entity);
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	u32 Scene::GetEntitiesCount()
	{
		return m_Registry.size();
	}

	bool Scene::HasPendingEntities()
	{
		return m_PendingEntities.size() > 0;
	}

	Entity Scene::NextPendingEntity()
	{
		Entity entity = m_PendingEntities.front();
		m_PendingEntities.pop();
		return entity;
	}
};
