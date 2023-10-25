#include "Engine/Renderer.hpp"
#include "Layers/ImGuiLayer.hpp"

namespace BetterThanNothing
{
	ImGuiLayer::ImGuiLayer(): Layer("ImGuiLayer")
	{

	}

	void ImGuiLayer::OnAttach(void)
	{

	}

	void ImGuiLayer::OnDetach(void)
	{

	}

	void ImGuiLayer::OnUpdate(float deltatime)
	{
		(void) deltatime;
	}

	void ImGuiLayer::OnRender(Renderer* pRenderer)
	{
		(void) pRenderer;

		ImGui_ImplVulkan_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::MenuItem("Hello world", "bip bip");
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		ImGui::Render();
	}
};
