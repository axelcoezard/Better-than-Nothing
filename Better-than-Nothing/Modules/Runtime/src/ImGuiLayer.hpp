#pragma once

#include <BetterThanNothing.hpp>

namespace BetterThanNothing
{
	class Renderer;
	class Event;

	class ImGuiLayer : public Layer
	{
		public:
			ImGuiLayer();
			~ImGuiLayer() = default;

			void OnAttach() override;
			void OnDetach() override;
			void OnUpdate(f32 deltatime) override;
			void OnRender(Renderer* pRenderer) override;
			void OnEvent(Event* pEvent) override;
	};
};
