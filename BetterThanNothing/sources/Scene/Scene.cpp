#include "Engine/Device.hpp"
#include "Engine/Renderer.hpp"
#include "Engine/Model.hpp"
#include "Events/Event.hpp"
#include "Scene/Scene.hpp"
#include "Scene/Camera.hpp"
#include "Scene/Light.hpp"

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

		for (uint32_t i = 0; i < m_pPointLights.size(); i++) {
			delete m_pPointLights[i];
		}

		for (uint32_t i = 0; i < m_pSpotLights.size(); i++) {
			delete m_pSpotLights[i];
		}

		delete m_pCamera;
	}

	Camera* Scene::InitCamera(double x, double y, double z, double yaw, double pitch)
	{
		m_pCamera = new Camera(x, y, z, yaw, pitch);
		return m_pCamera;
	}

	DirectionalLight* Scene::InitDirectionalLight(glm::vec3 color, float ambientIntensity, float diffuseIntensity, glm::vec3 direction)
	{
		m_pDirectionalLight = new DirectionalLight();
		m_pDirectionalLight->m_Color = color;
		m_pDirectionalLight->m_AmbientIntensity = ambientIntensity;
		m_pDirectionalLight->m_DiffuseIntensity = diffuseIntensity;
		m_pDirectionalLight->m_Direction = direction;
		return m_pDirectionalLight;
	}

	PointLight* Scene::AddPointLight(glm::vec3 color, float ambientIntensity, float diffuseIntensity, glm::vec3 position, float constant, float linear, float quadratic)
	{
		PointLight* pPointLight = new PointLight();
		pPointLight->m_Color = color;
		pPointLight->m_AmbientIntensity = ambientIntensity;
		pPointLight->m_DiffuseIntensity = diffuseIntensity;
		pPointLight->m_Position = position;
		pPointLight->m_Constant = constant;
		pPointLight->m_Linear = linear;
		pPointLight->m_Quadratic = quadratic;
		return pPointLight;
	}

	SpotLight* Scene::AddSpotLight(glm::vec3 color, float ambientIntensity, float diffuseIntensity, glm::vec3 position, glm::vec3 direction, float constant, float linear, float quadratic, float cutOff, float outerCutOff)
	{
		PointLight* pPointLight = AddPointLight(color, ambientIntensity, diffuseIntensity, position, constant, linear, quadratic);
		SpotLight* pSpotLight = static_cast<SpotLight*>(pPointLight);
		pSpotLight->m_Direction = direction;
		pSpotLight->m_CutOff = cutOff;
		pSpotLight->m_OuterCutOff = outerCutOff;
		return pSpotLight;
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
