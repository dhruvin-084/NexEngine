#ifndef EVENT_H_
#define EVENT_H_

#include"Nex/Core.h"

#include<string>
namespace Nex {
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication     = BIT(0),
		EventCategoryInput           = BIT(1),
		EventCategoryKeyboard        = BIT(2),
		EventCategoryMouse           = BIT(3)
	};

	class NEX_API Event {
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() = 0;
		virtual const char* GetEventName() = 0;
		virtual int GetCategoryFlags() = 0;
		virtual std::string ToString() { return GetEventName(); }
		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_Handled = false;
	};

	// TODO: Impliment Event dispatcher
	
	class EventDispatcher {
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template<typename T>
		bool Dispatch(std::function<bool(T&)> func) {

			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		 Event& m_Event;
	};
	
	// << overload
	inline std::ostream& operator <<(std::ostream& os, Event& e) {
		return os << e.ToString();
	}

}
#endif // !EVENT_H_

