#pragma once

namespace BetterThanNothing
{
	class DrawStreamBuilder;
	class Model;
	class Camera;
	class Event;

	class Scene
	{
	private:
		u32						m_Id;
		std::string				m_Name;

		Camera*					m_pCamera;
		std::vector<Model*>		m_pModels;
		std::queue<Model*>		m_pModelsWaiting;
	public:
								Scene(u32 id, std::string_view name);
								~Scene();

								Scene(const Scene&) = delete;
		Scene&					operator=(const Scene&) = delete;
								Scene(Scene&&) = delete;
		Scene&					operator=(Scene&&) = delete;

	public:
		Camera*					InitCamera(f64 x, f64 y, f64 z, f64 yaw, f64 pitch);
		Model*					LoadModel(const std::string& modelPath, const std::string& texturePath);

		void					OnUpdate(f32 deltatime);
		void					OnEvent(Event* pEvent);

	public:
		u32						GetId()		{ return m_Id; }
		std::string&			GetName()	{ return m_Name; }
		Camera*					GetCamera()	{ return m_pCamera; }
		std::vector<Model*>&	GetModels()	{ return m_pModels; }
		bool					HasWaitingModels() { return m_pModelsWaiting.size() > 0; }

		Model*					GetNextWaitingModel()
		{
			auto model = m_pModelsWaiting.front();
			m_pModelsWaiting.pop();
			m_pModels.push_back(model);
			return model;
		}
	};
};
