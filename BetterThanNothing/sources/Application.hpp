#pragma once

namespace BetterThanNothing
{
	class Window;
	class Device;
	class Renderer;
	class LayerStack;
	class Event;

	class Application
	{
	protected:
		Window* m_pWindow;
		Device* m_pDevice;
		Renderer* m_pRenderer;
		LayerStack* m_pLayerStack;
	public:
		Application(std::string_view title, uint32_t width, uint32_t height);
		virtual ~Application();

		void Run();

		virtual void OnEnable() = 0;
		virtual void OnDisable() = 0;
		virtual void OnUpdate(float deltatime) = 0;
		virtual void OnRender(Renderer* renderer) = 0;
		virtual void OnEvent(Event* event) = 0;
	};
};
