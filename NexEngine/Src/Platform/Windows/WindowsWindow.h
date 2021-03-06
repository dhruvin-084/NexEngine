#ifndef WINDOWSWINDOW_H_
#define WINDOWSWINDOW_H_

#include"Nex/Window.h"
#include"Nex/Renderer/GraphicsContext.h"

namespace Nex {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProp& prop);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline virtual void* GetNativeWindow() const override { return m_Window; }

		virtual void SetEventCallback(const std::function<void(Event&)>& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	private:
		virtual void Init(const WindowProp& prop);
		virtual void ShutDown();
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			std::function<void(Event&)> EventCallback;
		};

		WindowData m_Data;
	};
}
#endif // !WINDOWSWINDOW_H_
