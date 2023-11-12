#pragma once

namespace BetterThanNothing
{
	class Renderer;
	class Model;
	class Camera;
	class Event;

	class Light;
	class DirectionalLight;
	class PointLight;
	class SpotLight;


	class Scene
	{
	private:
		std::string					m_Name;

		Camera*						m_pCamera;

		DirectionalLight*			m_pDirectionalLight;
		std::vector<PointLight*>	m_pPointLights;
		std::vector<SpotLight*>		m_pSpotLights;

		std::vector<Model*>			m_pModels;
	public:
									Scene(std::string_view name);
									~Scene();

									Scene(const Scene&) = delete;
		Scene&						operator=(const Scene&) = delete;
									Scene(Scene&&) = delete;
		Scene&						operator=(Scene&&) = delete;

	public:
		Camera*						InitCamera(double x, double y, double z, double yaw, double pitch);

		DirectionalLight* 			InitDirectionalLight(glm::vec3 color, float ambientIntensity, float diffuseIntensity, glm::vec3 direction);
		PointLight*					AddPointLight(glm::vec3 color, float ambientIntensity, float diffuseIntensity, glm::vec3 position, float constant, float linear, float quadratic);
		SpotLight*					AddSpotLight(glm::vec3 color, float ambientIntensity, float diffuseIntensity, glm::vec3 position, glm::vec3 direction, float constant, float linear, float quadratic, float cutOff, float outerCutOff);
		void						LoadModel(Renderer* pRenderer, const std::string& modelPath, const std::string& texturePath);

		void						Update(float deltatime);
		void						Render(Renderer* pRenderer);
		void						OnEvent(Event* pEvent);

	public:
		std::string&				GetName()	{ return m_Name; }
		Camera*						GetCamera()	{ return m_pCamera; }
		DirectionalLight*			GetDirectionalLight()	{ return m_pDirectionalLight; }
		std::vector<PointLight*>&	GetPointLights()	{ return m_pPointLights; }
		std::vector<SpotLight*>&	GetSpotLights()	{ return m_pSpotLights; }
		std::vector<Model*>&		GetModels()	{ return m_pModels; }
	};
};
