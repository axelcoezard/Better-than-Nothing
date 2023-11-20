#pragma once

namespace BetterThanNothing
{
	class Window;
	class Device;
	class Renderer;

	class ModelPool;
	class TexturePool;

	class Scene;
	class Event;

	class Application
	{
	protected:
		Window*				m_Window;
		Device*				m_Device;
		Renderer*			m_Renderer;

		ModelPool*			m_ModelPool;
		TexturePool*		m_TexturePool;

		std::vector<Scene*>	m_Scenes;
		u32					m_CurrentSceneId;
	public:
							Application(std::string_view title, u32 width, u32 height);
		virtual				~Application();

		void				Run();

		virtual void		OnEnable() = 0;
		virtual void		OnDisable() = 0;

		void				OnEvent(Event* event);

		Scene*				CreateScene(const std::string& name);

		Window*				GetWindow() { return m_Window; }
		Device*				GetDevice() { return m_Device; }
		Renderer*			GetRenderer() { return m_Renderer; }
	};
};
