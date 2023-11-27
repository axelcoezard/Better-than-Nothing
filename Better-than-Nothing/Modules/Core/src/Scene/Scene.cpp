#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	Scene::Scene(u32 id, std::string_view name, ModelPool* modelPool, TexturePool* texturePool)
	{
		m_Id = id;
		m_Name = name;
		m_ModelPool = modelPool;
		m_TexturePool = texturePool;
		m_ECSManager = new ECSManager();
	}

	Scene::~Scene()
	{
		delete m_Camera;
	}

	Camera* Scene::InitCamera(f64 x, f64 y, f64 z, f64 yaw, f64 pitch)
	{
		m_Camera = new Camera(x, y, z, yaw, pitch);
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

		Entity entity = m_ECSManager->CreateEntity();
		m_ECSManager->AddComponent<ModelComponent>(entity, modelComponent);
		m_ECSManager->AddComponent<TransformComponent>(entity, transformComponent);
		m_PendingEntities.push(entity);
		return entity;
	}

	void Scene::OnUpdate(f32 deltatime)
	{
		m_Camera->Update(deltatime);

		f32 speed = 1.5f;
		f32 rotation = glm::mod(speed * 30.0f * (f32) glfwGetTime() * 1.5f, 360.0f);

		m_ECSManager->GetView<TransformComponent>().each([&](auto entity, TransformComponent& transform) {
			(void) entity;
			transform.rotation = glm::vec3(0.0f, (f32) rotation, 0.0f);
		});
	}

	void Scene::OnEvent(Event* pEvent)
	{
		m_Camera->OnEvent(pEvent);
	}
};
