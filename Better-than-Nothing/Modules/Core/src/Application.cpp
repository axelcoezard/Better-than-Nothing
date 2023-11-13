#include "Application.hpp"

#include "Renderer/Window.hpp"
#include "Renderer/Device.hpp"
#include "Renderer/Renderer.hpp"
#include "Layers/LayerStack.hpp"
#include "Events/Event.hpp"

namespace BetterThanNothing
{
	Application::Application(std::string_view title, uint32_t width, uint32_t height)
	{
		m_pWindow = new Window(title, width, height);
		m_pWindow->SetEventCallback(BIND_EVENT_LISTENER(OnEvent));

		m_pDevice = new Device(m_pWindow);
		m_pRenderer = new Renderer(m_pWindow, m_pDevice);
		m_pLayerStack = new LayerStack();
	}

	Application::~Application(void)
	{
		delete m_pLayerStack;
		delete m_pRenderer;
		delete m_pDevice;
		delete m_pWindow;
	}

	void Application::Run(void)
	{
		OnEnable();

		float deltatime = 0.0f;
		float lastFrame = 0.0f;
		float frameTime = 1.0f / 240.0f;
		uint32_t frameCount = 0;

		for (auto it = m_pLayerStack->Begin(); it != m_pLayerStack->End(); ++it) {
			(*it)->OnAttach();
		}

		while (!m_pWindow->ShouldClose()) {
			m_pWindow->Poll();

			float currentFrame = glfwGetTime();
			deltatime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			frameCount += 1;

			for (auto it = m_pLayerStack->Begin(); it != m_pLayerStack->End(); ++it) {
				(*it)->OnUpdate(deltatime);
			}

			if (m_pRenderer->BeginRender()) {
				for (auto it = m_pLayerStack->Begin(); it != m_pLayerStack->End(); ++it) {

					(*it)->OnRender(m_pRenderer);
				}

				m_pRenderer->EndRender();
			}

			//std::cout.precision(3);
			//std::cout << "\033[2J\033[1;1H";
			//std::cout << "Vendor: " << m_pDevice->GetVendorName() << std::endl;
			//std::cout << "Device: " << m_pDevice->GetDeviceName() << std::endl;
			//std::cout << "API version: " << m_pDevice->GetApiVersion() << std::endl;
			//std::cout << "Frame time: " << deltatime * 1000 << "ms (" << (1.0f / deltatime) << " fps) " << std::endl;
			//std::cout << "Frame count: " << frameCount << std::endl;

			useconds_t frameTimeMicroseconds = static_cast<useconds_t>(frameTime * 1000000);
			float elapsedTime = glfwGetTime() - currentFrame;
			if (elapsedTime < frameTime) {
				usleep(frameTimeMicroseconds - static_cast<useconds_t>(elapsedTime * 1000000));
			}
		}

		m_pDevice->Idle();

		for (auto it = m_pLayerStack->Begin(); it != m_pLayerStack->End(); ++it) {
			(*it)->OnDetach();
		}

		OnDisable();
	}
};
