#pragma once
#include "pch.h"
#include "RealEngine/PlatformMacros.h"

/// <summary>
/// This is a stopping event system so each event must be taken care of before the next one can continue, Eventually
/// an event buffer will be needed to properly dispatch events as to not hold up execution
/// </summary>
namespace Real
{
	enum class EventType
	{
		//enum class for preventing scope collision and static calls
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	enum EventCatagory
	{
		//bit shifting for simple & comparison checks allowing for multiple categories for an event
		None = 0,
		EventCategoryApplication = 1 << 0,
		EventCategoryInput = 1 << 1,
		EventCategoryKeyboard = 1 << 2,
		EventCategoryMouse = 1 << 3,
		EventCategoryMouseButton = 1 << 4
	};
	/// <summary>
	/// Event is an abstract class that is the parent for all other event interaction classes
	/// </summary>
	
	class REAL_EXPORT Event
	{
	public:
		bool m_eventHandled = false;

		virtual ~Event() = default;
		friend class EventDispather;

		virtual EventType   GetEventType()     const = 0;
		virtual int		    GetCategoryFlags() const = 0;
		virtual const char* GetName()		   const = 0; //public access for debuging
		virtual std::string ToString()		   const { return GetName(); }

		inline bool IsInCategory(EventCatagory category)
		{
			return GetCategoryFlags() & category;
		}
		
	};
	/// <summary>
	/// This technique is from the Cherno. If recieving an Event (OnEvent() is called), this will be recieved as a reference of any type of event.
	/// Thus EventDispatcher can be called and the Dispatch function used to dispatch a function based on it's type easily. The lamda function is called when
	/// the Dispatch() matches
	/// </summary>
	class EventDispatcher
	{

	public:
		EventDispatcher(Event& event)
			:m_event(event) {}

		//if function you are trying to dispatch matches the dispatch type. run that function
		//compiler determines type of F ex call: dispatcher.Dispatch<WindowResizeEvent>(lamdaFunc)=====> lambdaFunc = [&](WindowResizeEvent& e){}
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_event.GetEventType() == T::GetStaticEventType())
			{
				m_event.m_eventHandled |= func(static_cast<T&>(m_event));
				return true;
			}
			return false;
		}
	private:
		Event& m_event;
		
	};

	
}
