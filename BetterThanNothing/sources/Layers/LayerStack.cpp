#include "Layers/LayerStack.hpp"
#include "Layers/Layer.hpp"

namespace BetterThanNothing
{
	LayerStack::LayerStack()
	{

	}

	LayerStack::~LayerStack()
	{
		for (Layer* pLayer : m_Layers)
		{
			delete pLayer;
		}
	}

	void LayerStack::PushLayer(Layer* pLayer)
	{
		m_Layers.emplace(m_Layers.begin(), pLayer);
	}

	void LayerStack::PushOverlay(Layer* pOverlay)
	{
		m_Layers.emplace_back(pOverlay);
	}

	void LayerStack::PopLayer(Layer* pLayer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), pLayer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}

	void LayerStack::PopOverlay(Layer* pOverlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), pOverlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}

	void LayerStack::ForEach(std::function<void(Layer*)> pFunction)
	{
		for (Layer* pLayer : m_Layers)
		{
			pFunction(pLayer);
		}
	}
};
