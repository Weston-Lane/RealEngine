#include "LayerStack.h"
#include "Logger.h"
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
		REAL_ASSERT(layer != nullptr, "layer is null!");
		layer->OnAttach();
	}
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_layerStack.begin(), m_layerStack.end(), layer);
		if (it != m_layerStack.end())
		{
			m_layerStack.erase(it);
			layer->OnDetach();
			delete layer;
			m_layerInsert--;
		}
	}
	void LayerStack::PushOverlayLayer(Layer* overlay)
	{
		m_layerStack.emplace_back(overlay);
		REAL_ASSERT(overlay != nullptr, "Overlay layer is null!");
		overlay->OnAttach();
	}
	void LayerStack::PopOverlayLayer(Layer* overlay)
	{
		auto it = std::find(m_layerStack.begin(), m_layerStack.end(), overlay);
		if(it != m_layerStack.end())
		{
			m_layerStack.erase(it); 
			overlay->OnDetach();
			delete overlay;
			
		}

	}
}
