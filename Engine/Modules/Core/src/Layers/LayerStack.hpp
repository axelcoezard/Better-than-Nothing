#pragma once

#include <vector>
#include "Layers/Layer.hpp"

namespace BetterThanNothing
{
	class LayerStack
	{
		private:
			std::vector<Layer*> m_Layers;
		public:
			LayerStack();
			~LayerStack();

			void PushLayer(Layer* pLayer);
			void PushOverlay(Layer* pOverlay);
			void PopLayer(Layer* pLayer);
			void PopOverlay(Layer* pOverlay);

			void ForEach(std::function<void(Layer*)> pFunction);

			std::vector<Layer*>::iterator Begin() { return m_Layers.begin(); }
			std::vector<Layer*>::iterator End() { return m_Layers.end(); }
	};
};
