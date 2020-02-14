#pragma once

namespace Meander
{
	struct WindowProperties
	{
		const char* Title;
		unsigned int Width;
		unsigned int Height;
		bool VerticalSync;

		WindowProperties(const char* title = "Meander", 
			unsigned int width = 1280,
			unsigned int height = 720,
			bool verticalSync = true)
			: Title(title), Width(width), Height(height), VerticalSync(verticalSync)
		{
		}
	};

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

		/* Resizes the window. */
		virtual void Resize(unsigned int width, unsigned int height) = 0;

		/* Returns the width of the window. */
		inline unsigned int GetWidth() const { return s_Properties.Width; }

		/* Returns the height of the window. */
		inline unsigned int GetHeight() const { return s_Properties.Height; }

		/* Returns the window aspect ratio. */
		inline float GetAspectRatio() const { return (float)GetWidth() / GetHeight(); }

		/* Returns the Window API. */
		virtual WindowAPI GetWindowAPI() = 0;
		
		/* Returns the window instance. */
		inline static Window* Get() { return s_Instance; }

	protected:
		static WindowProperties s_Properties;
		static Window* s_Instance;
	};
}