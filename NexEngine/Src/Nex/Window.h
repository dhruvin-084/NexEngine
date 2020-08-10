#ifndef WINDOW_H_
#define WINDOW_H_

#include"nexpch.h"

#include"Core.h"
#include"Events/Event.h"

namespace Nex {

	struct WindowProp {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProp(std::string title = "Nex Engine", unsigned int w = 1280, unsigned int h = 720)
			:Title(title), Width(w), Height(h) {}
	};

	class NEX_API Window {
	public:
		virtual ~Window() {}

		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const std::function<void(Event&)>& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProp& peop = WindowProp());
		
	};
}
#endif // !WINDOW_H_
