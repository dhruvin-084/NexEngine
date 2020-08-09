#ifndef APPLICATIONEVENT_H_
#define APPLICATIONEVENT_H_

#include"Event.h"


namespace Nex{

	class NEX_API WindowResizeEvent : public Event {

	public:
		WindowResizeEvent(int width, int height)
			: m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }


		virtual int GetCategoryFlags() override { return EventCategoryApplication; }
		static EventType GetStaticType() { return EventType::WindowResize; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual const char* GetEventName() override { return "WindowResize"; }

		virtual std::string ToString() override {
			std::stringstream ss;
			ss << "WindowResize: " << m_Width << "," << m_Height;
			return ss.str();
		}
	private:
		unsigned int m_Width, m_Height;
	};

	class NEX_API WindowClose : public Event {
	public: 
		WindowClose() {}
		virtual int GetCategoryFlags() override { return EventCategoryApplication; }
		static EventType GetStaticType() { return EventType::WindowClose; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual const char* GetEventName() override { return "WindowClose"; }
	};

	class NEX_API AppTickEvent : public Event {
	public:
		AppTickEvent() {}
		virtual int GetCategoryFlags() override { return EventCategoryApplication; }
		static EventType GetStaticType() { return EventType::AppTick; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual const char* GetEventName() override { return "AppTick"; }
	};

	class NEX_API AppUpdateEvent : public Event {
	public:
		AppUpdateEvent() {}
		virtual int GetCategoryFlags() override { return EventCategoryApplication; }
		static EventType GetStaticType() { return EventType::AppUpdate; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual const char* GetEventName() override { return "AppUpdate"; }
	};

	class NEX_API AppRenderEvent : public Event {
	public:
		AppRenderEvent() {}
		virtual int GetCategoryFlags() override { return EventCategoryApplication; }
		static EventType GetStaticType() { return EventType::AppRender; }
		virtual EventType GetEventType() override { return GetStaticType(); }
		virtual const char* GetEventName() override { return "AppRender"; }
	};


}

#endif // !APPLICATIONEVENT_H_
