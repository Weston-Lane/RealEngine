#include "LayerStack.h"

namespace Real
{
	LayerStack::LayerStack()
	{
		m_layerInsert = m_layerStack.begin();
	}
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_layerStack)
			{ delete layer; }
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_layerInsert = m_layerStack.emplace(m_layerInsert, layer);
	}
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_layerStack.begin(), m_layerStack.end(), layer);
		if (it != m_layerStack.end())
		{
			m_layerStack.erase(it);
			m_layerInsert--;
		}
	}
	void LayerStack::PushOverlayLayer(Layer* overlay)
	{
		m_layerStack.emplace_back(overlay);
	}
	void LayerStack::PopOverlayLayer(Layer* overlay)
	{
		auto it = std::find(m_layerStack.begin(), m_layerStack.end(), overlay);
		if(it != m_layerStack.end())
			{ m_layerStack.erase(it); }

	}
}
