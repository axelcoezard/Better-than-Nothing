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

		m_ModelPool = new ModelPool("/home/acoezard/lab/better-than-nothing/Assets/Models/", m_Device);
		m_TexturePool = new TexturePool("/home/acoezard/lab/better-than-nothing/Assets/Models/", m_Device);

		m_Renderer = new Renderer(m_Window, m_Device);
		m_Renderer->LoadPipeline("main", "main/main.vert.spv", "main/main.frag.spv");
	}

	Application::~Application()
	{
		for (auto & scene : m_Scenes) {
			delete scene;
		}

		delete m_TexturePool;
		delete m_ModelPool;

		delete m_Renderer;
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

		while (!m_Window->ShouldClose()) {
			m_Window->Poll();

			f32 currentFrame = glfwGetTime();
			deltatime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			frameCount += 1;

			m_Scenes[m_CurrentSceneId]->OnUpdate(deltatime);
			m_Renderer->Render(m_Scenes[m_CurrentSceneId]);
			m_Device->WaitIdle();

			std::cout.precision(3);
			std::cout << "\033[2J\033[1;1H";
			std::cout << "Vendor: " << m_Device->GetVendorName() << std::endl;
			std::cout << "Device: " << m_Device->GetDeviceName() << std::endl;
			std::cout << "API version: " << m_Device->GetApiVersion() << std::endl;
			std::cout << "Frame time: " << deltatime * 1000 << "ms (" << (1.0f / deltatime) << " fps) " << std::endl;
			std::cout << "Frame count: " << frameCount << std::endl;
			std::cout << "Scene: " << m_Scenes[m_CurrentSceneId]->GetName() << std::endl;
			std::cout << "Entities count: " << m_Scenes[m_CurrentSceneId]->GetECSManager()->GetEntitiesCount() << std::endl;

			useconds_t frameTimeMicroseconds = static_cast<useconds_t>(frameTime * 1000000);
			f32 elapsedTime = glfwGetTime() - currentFrame;
			if (elapsedTime < frameTime) {
				usleep(frameTimeMicroseconds - static_cast<useconds_t>(elapsedTime * 1000000));
			}
		}

		OnDisable();
	}

	void Application::OnEvent(Event* event)
	{
		m_Scenes[m_CurrentSceneId]->OnEvent(event);
	}

	Scene* Application::CreateScene(const std::string& name)
	{
		auto scene = new Scene(m_Scenes.size(), name, m_ModelPool, m_TexturePool);
		m_Scenes.push_back(scene);
		m_CurrentSceneId = scene->GetId();
		return scene;
	}
};
