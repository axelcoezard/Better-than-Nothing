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
		Window*				m_pWindow;
		Device*				m_pDevice;
		Renderer*			m_pRenderer;

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

		Window*				GetWindow() { return m_pWindow; }
		Device*				GetDevice() { return m_pDevice; }
		Renderer*			GetRenderer() { return m_pRenderer; }
	};
};
