#include "Sandbox.hpp"
#include "Application.hpp"
#include "Engine/Window.hpp"
#include "Engine/Device.hpp"
#include "Engine/Renderer.hpp"
#include "Scene/Scene.hpp"
#include "Layers/LayerStack.hpp"
#include "Layers/ImGuiLayer.hpp"
#include "Layers/SceneLayer.hpp"
#include "Events/EventDispatcher.hpp"
#include "Events/KeyEvent.hpp"

namespace BetterThanNothing
{
	void Sandbox::OnEnable()
	{
		m_pRenderer->LoadPipeline(
			"main",
			"/home/acoezard/lab/better-than-nothing/Assets/Shaders/vert.spv",
			"/home/acoezard/lab/better-than-nothing/Assets/Shaders/frag.spv");

		Scene* pScene = new Scene("world");

		pScene->LoadModel(
			m_pRenderer,
			"/home/acoezard/lab/better-than-nothing/Assets/Models/42/42.obj",
			"/home/acoezard/lab/better-than-nothing/Assets/Models/42/42.jpg");

		pScene->LoadModel(
			m_pRenderer,
			"/home/acoezard/lab/better-than-nothing/Assets/Models/viking_room/viking_room.obj",
			"/home/acoezard/lab/better-than-nothing/Assets/Models/viking_room/viking_room.png");

		pScene->LoadModel(
			m_pRenderer,
			"/home/acoezard/lab/better-than-nothing/Assets/Models/robot/robot.obj",
			"/home/acoezard/lab/better-than-nothing/Assets/Models/robot/robot.png");

		m_pRenderer->Prepare(pScene);

		m_pLayerStack->PushLayer(new ImGuiLayer());
		m_pLayerStack->PushLayer(new SceneLayer(pScene));
	}

	void Sandbox::OnDisable()
	{

	}

	void Sandbox::OnEvent(Event* event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressEvent>(OnKeyPress);
	}

	void Sandbox::OnUpdate(float deltatime)
	{
		(void) deltatime;
	}

	void Sandbox::OnRender(Renderer* renderer)
	{
		(void) renderer;
	}

	bool Sandbox::OnKeyPress(KeyPressEvent* event)
	{
		std::cout << event->GetName() << " => " << event->GetKey() << std::endl;
		return true;
	}
};

BetterThanNothing::Application* CreateApplication()
{
	return new BetterThanNothing::Sandbox("better-than-nothing", 700, 700);
}
