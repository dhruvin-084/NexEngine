#ifndef WINDOWSINPUT_H_
#define WINDOWSINPUT_H_

#include"Nex/Input.h"

namespace Nex {
	class WindowsInput : public Input {
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}
#endif // !WINDOWSINPUT_H_
