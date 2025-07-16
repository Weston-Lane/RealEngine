#pragma once
#include "PlatformMacros.h"
#include "Layer.h"

/// <summary>
/// Layer Stack is owned by the application so when application shuts down the Layer stack will deallocate all it's layers
///  Layers can be pushed Poped or inserted into the proper position.
/// The layers lifetime is determined by the container so m_layerStack in this case
/// </summary>
namespace Real
{
	class REAL_EXPORT LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlayLayer(Layer* overlay);
		void PopOverlayLayer(Layer* overlay);

		std::vector<Layer*> GetLayerStack() { return m_layerStack; }

		std::vector<Layer*>::iterator Begin() { return m_layerStack.begin(); }
		std::vector<Layer*>::iterator End() { return m_layerStack.end(); }

	private:
		std::vector<Layer*> m_layerStack;
		std::vector<Layer*>::iterator m_layerInsert; // will point to next available pos in stack of the last non-overlay layer
	};
}
