#ifndef KEYEVENT_H_
#define KEYEVENT_H_

#include"Event.h"
#include<sstream>

namespace Nex {


	class NEX_API KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return m_KeyCode; }
		virtual int GetCategoryFlags() override { return EventCategoryInput | EventCategoryKeyboard; }
	protected:
		KeyEvent(int keyCode)
			:m_KeyCode(keyCode) {}

		int m_KeyCode;
	};



	class NEX_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keyCode, int repeatCout)
			: KeyEvent(keyCode), m_RepeatCount(repeatCout) {}

		static EventType GetStaticType() { return EventType::KeyPressed;  }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual const char* GetEventName() override { return "KeyPressed"; }
		virtual std::string ToString() override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << "(" << m_RepeatCount << "repeats)";
			return ss.str();
		}

	private:
		int m_RepeatCount;

	};



	class NEX_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keyCode)
			: KeyEvent(keyCode) {}

		static EventType GetStaticType() { return EventType::KeyReleased; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual const char* GetEventName() override { return "KeyReleased"; }
		virtual std::string ToString() override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode ;
			return ss.str();
		}
	};

	class NEX_API KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(int keyCode)
			: KeyEvent(keyCode) {}

		static EventType GetStaticType() { return EventType::KeyTyped; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual const char* GetEventName() override { return "KeyTyped"; }
		virtual std::string ToString() override {
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}
	};
}
#endif // !KEYEVENT_H_
