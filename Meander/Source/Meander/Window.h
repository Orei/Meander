#pragma once
#include "WindowProperties.h"
#include "Input/Key.h"
#include "Input/InputAction.h"
#include "Input/MouseButton.h"

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

		/* Registers the callback function called when the window is resized. */
		void RegisterResizeCallback(std::function<void(uint32_t, uint32_t)> callback) { m_ResizeCallback = callback; }

		/* Registers the callback function called when the window processes a key event. */
		void RegisterKeyCallback(std::function<void(Key, InputAction)> callback) { m_KeyCallback = callback; }

		/* Registers the callback function called when the window processes a mouse button event. */
		void RegisterMouseButtonCallback(std::function<void(MouseButton, InputAction)> callback) { m_MouseButtonCallback = callback; }

		/* Registers the callback function called when the window processes a cursor position event. */
		void RegisterCursorPositionCallback(std::function<void(double, double)> callback) { m_CursorPositionCallback = callback; }

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
		std::function<void(uint32_t, uint32_t)> m_ResizeCallback;
		std::function<void(Key, InputAction)> m_KeyCallback;
		std::function<void(MouseButton, InputAction)> m_MouseButtonCallback;
		std::function<void(double, double)> m_CursorPositionCallback;

		static WindowProperties s_Properties;
		static Window* s_Instance;
	};
}
