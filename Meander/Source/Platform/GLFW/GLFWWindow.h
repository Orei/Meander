#pragma once
#include "Meander/Window.h"

struct GLFWwindow;

namespace Meander
{
	class GLFWWindow : public Window
	{
	public:
		virtual void Initialize(const WindowProperties& properties) override;
		virtual void PollEvents() override;
		virtual void Present() override;
		virtual bool IsClosing() override;

		virtual void* GetProcessAddress() override;

		inline const GLFWwindow* GetNativeWindow() const { return m_NativeWindow; }

	private:
		GLFWwindow* m_NativeWindow = nullptr;
	};
}