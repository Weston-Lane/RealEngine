#pragma once
/// <summary>
/// Layer Interface class. Holds the list of layers with specific ordering for rendering layers correctly
/// Events happen in reverse to prevent multi layer event handling and proper order of event handling
/// Ex:Game Layer, Debug Layer, UI Layer, ect...
/// each new layer is a child of this class and gets pushed into the layer stack
/// </summary>
#include "pch.h"
#include "PlatformMacros.h"
#include "Events/Event.h"
namespace Real
{
	class REAL_EXPORT Layer
	{
	public:
		Layer(const std::string& layerName = "Layer")
			:m_layerName(layerName), m_enabled(true) {}
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}
		
		inline std::string GetLayerName() const { return m_layerName; }
	protected:
		std::string m_layerName;
		bool m_enabled;
		void SetEnabled(bool enabled) { m_enabled = enabled; }
	};
}
