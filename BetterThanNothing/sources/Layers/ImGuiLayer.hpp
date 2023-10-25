#pragma once

#include "Layers/Layer.hpp"

namespace BetterThanNothing
{
	class Renderer;

	class ImGuiLayer : public Layer
	{
		public:
			ImGuiLayer();
			~ImGuiLayer() = default;

			void OnAttach() override;
			void OnDetach() override;
			void OnUpdate(float deltatime) override;
			void OnRender(Renderer* pRenderer) override;
	};
};
