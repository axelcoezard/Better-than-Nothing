#pragma once

namespace BetterThanNothing
{
	class Renderer;
	class Model;
	class Camera;
	class Event;

	class Scene
	{
	private:
		std::string				m_Name;

		Camera*					m_pCamera;
		std::vector<Model*>		m_pModels;
	public:
								Scene(std::string_view name);
								~Scene();

								Scene(const Scene&) = delete;
		Scene&					operator=(const Scene&) = delete;
								Scene(Scene&&) = delete;
		Scene&					operator=(Scene&&) = delete;

	public:
		Camera*					InitCamera(f64 x, f64 y, f64 z, f64 yaw, f64 pitch);
		void					LoadModel(Renderer* pRenderer, const std::string& modelPath, const std::string& texturePath);

		void					Update(f32 deltatime);
		void					Render(Renderer* pRenderer);
		void					OnEvent(Event* pEvent);

	public:
		std::string&			GetName()	{ return m_Name; }
		Camera*					GetCamera()	{ return m_pCamera; }
		std::vector<Model*>&	GetModels()	{ return m_pModels; }
	};
};
