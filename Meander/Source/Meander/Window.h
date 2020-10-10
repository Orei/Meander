#pragma once
#include "WindowProperties.h"

namespace Meander
{
	enum class WindowAPI
	{
		GLFW
	};

	class Window
	{
	public:
		Window();
		virtual ~Window();

		/* Initializes the window. */
		virtual void Initialize(const WindowProperties& properties) = 0;

		/* Enables or disables vertical synchronization. */
		virtual void SetVerticalSync(bool enabled) = 0;

		/* Enables or disables the cursor. */
		virtual void SetCursorState(bool enabled) = 0;
		
		/* Polls for events. */
		virtual void PollEvents() = 0;

		/* Presents the back-buffer to the window. */
		virtual void Present() = 0;

		/* Whether the window is requesting the program to close. */
		virtual bool IsClosing() = 0;

		/* Resizes the window. Ensure callback is called. */
		virtual void Resize(uint32_t width, uint32_t height) = 0;

		/* Sets the callback function called when the window is resized. */
		void SetOnResizeCallback(std::function<void(uint32_t, uint32_t)> callback) { m_OnResize = callback; }

		/* Returns the width of the window. */
		inline uint32_t GetWidth() const { return s_Properties.Width; }

		/* Returns the height of the window. */
		inline uint32_t GetHeight() const { return s_Properties.Height; }

		/* Returns the window aspect ratio. */
		inline float GetAspectRatio() const { return GetWidth() / (float)GetHeight(); }

		/* Returns the Window API. */
		virtual WindowAPI GetWindowAPI() = 0;
		
		/* Returns the window instance. */
		inline static Window* Get() { return s_Instance; }

	protected:
		std::function<void(uint32_t, uint32_t)> m_OnResize;

		static WindowProperties s_Properties;
		static Window* s_Instance;
	};
}
