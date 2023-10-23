#pragma once

namespace BetterThanNothing
{
	class Renderer;
	class Model;
	class Camera;

	class Scene
	{
	private:
		std::string				m_Name;

		Camera*				m_pCamera;
		std::vector<Model*>		m_pModels;
	public:
								Scene(std::string_view name);
								~Scene();

								Scene(const Scene&) = delete;
		Scene&					operator=(const Scene&) = delete;
								Scene(Scene&&) = delete;
		Scene&					operator=(Scene&&) = delete;

	public:
		Camera*				InitCamera(double x, double y, double z, double yaw, double pitch);
		void					LoadModel(Renderer* pRenderer, const std::string& modelPath, const std::string& texturePath);

		void					Update(float deltatime);

	public:
		std::string&			GetName()	{ return m_Name; }
		Camera*				GetCamera()	{ return m_pCamera; }
		std::vector<Model*>&	GetModels()	{ return m_pModels; }
	};
};
