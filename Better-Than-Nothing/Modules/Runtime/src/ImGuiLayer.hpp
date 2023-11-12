#pragma once

#include <Layers/Layer.hpp>

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
			void OnUpdate(float deltatime) override;
			void OnRender(Renderer* pRenderer) override;
			void OnEvent(Event* pEvent) override;
	};
};
