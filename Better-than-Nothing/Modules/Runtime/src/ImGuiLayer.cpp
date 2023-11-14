#include "ImGuiLayer.hpp"

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

	void ImGuiLayer::OnUpdate(f32 deltatime)
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
		ImGui_ImplVulkan_RenderDrawData(
			ImGui::GetDrawData(),
			pRenderer->GetSwapChain()->GetCurrentCommandBuffer());
	}

	void ImGuiLayer::OnEvent(Event* pEvent)
	{
		(void) pEvent;
	}
};
