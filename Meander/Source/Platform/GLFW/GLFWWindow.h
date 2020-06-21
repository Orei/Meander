#pragma once
#include "Meander/Window.h"

struct GLFWwindow;

namespace Meander
{
	class GLFWWindow : public Window
	{
	public:
		/* Initializes the window. */
		virtual void Initialize(const WindowProperties& properties) override;

		/* Enables or disables vertical synchronization. */
		virtual void SetVerticalSync(bool enabled) override;

		/* Enables or disables the cursor. */
		virtual void SetCursorState(bool enabled) override;

		/* Polls for events. */
		virtual void PollEvents() override;

		/* Presents the back-buffer to the window. */
		virtual void Present() override;
		
		/* Whether the window is requesting the program to close. */
		virtual bool IsClosing() override;

		/* Resizes the window. */
		virtual void Resize(unsigned int width, unsigned int height) override;

		/* Returns the window API. */
		virtual WindowAPI GetWindowAPI() override { return WindowAPI::GLFW; }

		/* Returns a pointer to the native GLFW window. */
		inline GLFWwindow* GetNativeWindow() const { return m_NativeWindow; }

	private:
		GLFWwindow* m_NativeWindow = nullptr;
	};
}