
#include <Application.hpp>
#include <Engine/Window.hpp>
#include <Engine/Device.hpp>
#include <Engine/Renderer.hpp>
#include <Scene/Scene.hpp>
#include <Layers/LayerStack.hpp>
#include <Events/EventDispatcher.hpp>
#include <Events/KeyEvent.hpp>

#include "Sandbox.hpp"
#include "ImGuiLayer.hpp"
#include "SceneLayer.hpp"

namespace BetterThanNothing
{
	void Sandbox::OnEnable()
	{
		m_pRenderer->LoadPipeline(
			"main",
			"/home/acoezard/lab/better-than-nothing/Engine/Shaders/vert.spv",
			"/home/acoezard/lab/better-than-nothing/Engine/Shaders/frag.spv");

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

		//m_pLayerStack->PushLayer(new ImGuiLayer());
		m_pLayerStack->PushLayer(new SceneLayer(pScene));
	}

	void Sandbox::OnDisable()
	{

	}

	void Sandbox::OnEvent(Event* event)
	{
		// dispatch event to layers
		for (auto it = m_pLayerStack->Begin(); it != m_pLayerStack->End(); ++it) {
			(*it)->OnEvent(event);
		}
	}

	void Sandbox::OnUpdate(float deltatime)
	{
		(void) deltatime;
	}

	void Sandbox::OnRender(Renderer* renderer)
	{
		(void) renderer;
	}
};

BetterThanNothing::Application* CreateApplication()
{
	return new BetterThanNothing::Sandbox("better-than-nothing", WINDOW_WIDTH, WINDOW_HEIGHT);
}
