#ifndef MOUSEEVENT_H_
#define MOUSEEVEBT_H_

#include"Event.h"

#include<sstream>
namespace Nex {

	class NEX_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		virtual int GetCategoryFlags() override { return EventCategoryInput | EventCategoryMouse; }
		static EventType GetStaticType() { return EventType::MouseMoved; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual const char* GetEventName() override { return "MouseMoved"; }

		virtual std::string ToString() override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << "," << m_MouseY;
			return ss.str();
		}

	private:
		float m_MouseX, m_MouseY;
	};

	class NEX_API MouseScrollEvent : public Event {
	public:
		MouseScrollEvent(float x, float y)
			: m_XOffset(x), m_YOffset(y) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		virtual int GetCategoryFlags() override { return EventCategoryInput | EventCategoryMouse; }
		static EventType GetStaticType() { return EventType::MouseScrolled; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual const char* GetEventName() override { return "MouseScrolled"; }

		virtual std::string ToString() override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_XOffset << "," << m_YOffset;
			return ss.str();
		}

	private:
		float m_XOffset, m_YOffset;
	};

	class NEX_API MouseButtonEvent : public Event {

	public:
		inline int GetMouseButton() const { return m_Button; }
		virtual int GetCategoryFlags() override { return EventCategoryInput | EventCategoryMouse; }

	protected:
		MouseButtonEvent(int button)
			:m_Button(button) {}

		int m_Button;
	};

	class NEX_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		static EventType GetStaticType() { return EventType::MouseButtonPressed; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual const char* GetEventName() override { return "MouseButtonPressed"; }
		virtual std::string ToString() override {
			std::stringstream ss;
			ss << "MouseButtonPressed: " << m_Button;
			return ss.str();
		}
	};

	class NEX_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		static EventType GetStaticType() { return EventType::MouseButtonReleased; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual const char* GetEventName() override { return "MouseButtonReleased"; }
		virtual std::string ToString() override {
			std::stringstream ss;
			ss << "MouseButtonReleased: " << m_Button;
			return ss.str();
		}
	};

}

#endif // !MOUSEEVENT_H_
