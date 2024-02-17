#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	Application::Application()
	{
		m_ConfigManager = new ConfigManager("/home/acoezard/lab/better-than-nothing/Better-than-Nothing/Config/");

		ConfigReader config = m_ConfigManager->Read("Config.ini");
		std::string windowTitle = config->Get("window", "title", "Application");
		u32 windowWidth = config->GetInteger("window", "width", 800);
		u32 windowHeight = config->GetInteger("window", "height", 600);

		m_Window = new Window(windowTitle, windowWidth, windowHeight);
		m_Window->SetEventCallback(BIND_EVENT_LISTENER(OnEvent));

		m_Device = new Device(m_Window);

		m_ResourceManager = new ResourceManager(m_Device, "/home/acoezard/lab/better-than-nothing/Assets/");

		m_Renderer = new Renderer(m_Window, m_Device, m_ResourceManager);
	}

	Application::~Application()
	{
		for (auto & scene : m_Scenes) {
			delete scene;
		}

		delete m_Renderer;

		delete m_ResourceManager;

		delete m_Device;
		delete m_Window;
		delete m_ConfigManager;
	}

	void Application::Run()
	{
		OnEnable();

		f32 deltatime = 0.0f;
		f32 lastFrame = 0.0f;
		f32 frameTime = 1.0f / 240.0f;
		u32 frameCount = 0;

		RendererDebugInfo debugInfo{};
		debugInfo.vendorName = m_Device->GetVendorName();
		debugInfo.deviceName = m_Device->GetDeviceName();
		debugInfo.apiVersion = m_Device->GetApiVersion();
		debugInfo.drawCalls = 0;
		debugInfo.totalDrawCalls = 0;
		debugInfo.sceneName = m_Scenes[m_CurrentSceneId]->GetName();
		debugInfo.sceneEntitiesCount = m_Scenes[m_CurrentSceneId]->GetEntitiesCount();

		m_Renderer->BeforeRender();

		while (!m_Window->ShouldClose())
		{
			m_Window->Poll();

			f32 currentFrame = glfwGetTime();
			deltatime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			frameCount += 1;

			debugInfo.frameCount = frameCount;
			debugInfo.frameTime = deltatime;

			m_Scenes[m_CurrentSceneId]->OnUpdate(deltatime);
			m_Renderer->Render(m_Scenes[m_CurrentSceneId], &debugInfo);
			m_Device->WaitIdle();

			useconds_t frameTimeMicroseconds = static_cast<useconds_t>(frameTime * 1000000);
			f32 elapsedTime = glfwGetTime() - currentFrame;
			if (elapsedTime < frameTime)
			{
				usleep(frameTimeMicroseconds - static_cast<useconds_t>(elapsedTime * 1000000));
			}
		}

		m_Renderer->AfterRender();

		OnDisable();
	}

	void Application::OnEvent(Event* event)
	{
		m_Scenes[m_CurrentSceneId]->OnEvent(event);
	}

	Scene* Application::CreateScene(const std::string& name)
	{
		auto scene = new Scene(m_Scenes.size(), name, m_Window, m_ResourceManager);
		m_Scenes.push_back(scene);
		m_CurrentSceneId = scene->GetId();
		return scene;
	}
};
