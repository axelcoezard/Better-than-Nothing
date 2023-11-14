#include "Application.hpp"

#include "Renderer/Window.hpp"
#include "Renderer/Device.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Model.hpp"
#include "Renderer/DrawStream.hpp"
#include "Events/Event.hpp"
#include "Scene/Scene.hpp"
#include "Scene/Camera.hpp"

namespace BetterThanNothing
{
	Application::Application(std::string_view title, u32 width, u32 height)
	{
		m_pWindow = new Window(title, width, height);
		m_pWindow->SetEventCallback(BIND_EVENT_LISTENER(OnEvent));

		m_pDevice = new Device(m_pWindow);
		m_pRenderer = new Renderer(m_pWindow, m_pDevice);
	}

	Application::~Application(void)
	{
		for (auto & scene : m_Scenes) {
			delete scene;
		}

		delete m_pRenderer;
		delete m_pDevice;
		delete m_pWindow;
	}

	void Application::Run(void)
	{
		OnEnable();

		f32 deltatime = 0.0f;
		f32 lastFrame = 0.0f;
		f32 frameTime = 1.0f / 240.0f;
		u32 frameCount = 0;

		while (!m_pWindow->ShouldClose()) {
			m_pWindow->Poll();

			f32 currentFrame = glfwGetTime();
			deltatime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			frameCount += 1;

			auto currentScene = m_Scenes[m_CurrentSceneId];

			currentScene->OnUpdate(deltatime);

			m_pRenderer->Render(currentScene);

			std::cout.precision(3);
			std::cout << "\033[2J\033[1;1H";
			std::cout << "Vendor: " << m_pDevice->GetVendorName() << std::endl;
			std::cout << "Device: " << m_pDevice->GetDeviceName() << std::endl;
			std::cout << "API version: " << m_pDevice->GetApiVersion() << std::endl;
			std::cout << "Frame time: " << deltatime * 1000 << "ms (" << (1.0f / deltatime) << " fps) " << std::endl;
			std::cout << "Frame count: " << frameCount << std::endl;
			std::cout << "Scene: " << currentScene->GetName() << std::endl;
			std::cout << "Camera position: " << currentScene->GetCamera()->GetPosition().x << ", " << currentScene->GetCamera()->GetPosition().y << ", " << currentScene->GetCamera()->GetPosition().z << std::endl;
			std::cout << "Camera rotation: " << currentScene->GetCamera()->GetYaw() << ", " << currentScene->GetCamera()->GetPitch() << std::endl;
			std::cout << "Models count: " << currentScene->GetModels().size() << std::endl;

			useconds_t frameTimeMicroseconds = static_cast<useconds_t>(frameTime * 1000000);
			f32 elapsedTime = glfwGetTime() - currentFrame;
			if (elapsedTime < frameTime) {
				usleep(frameTimeMicroseconds - static_cast<useconds_t>(elapsedTime * 1000000));
			}
		}

		m_pDevice->Idle();

		OnDisable();
	}

	void Application::OnEvent(Event* event)
	{
		m_Scenes[m_CurrentSceneId]->OnEvent(event);
	}

	Scene* Application::CreateScene(std::string_view name)
	{
		auto scene = new Scene(m_Scenes.size(), name);
		m_Scenes.push_back(scene);
		m_CurrentSceneId = scene->GetId();
		return scene;
	}
};
