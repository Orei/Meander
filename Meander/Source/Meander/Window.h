#pragma once

// CreateWindow is defined elsewhere
#undef CreateWindow

namespace Meander
{
	struct WindowProperties
	{
		const char* Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(const char* title = "Meander", 
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class Window
	{
	public:
		Window();
		virtual ~Window();

		virtual void Initialize(const WindowProperties& properties) = 0;
		virtual void PollEvents() = 0;
		virtual void Present() = 0;
		virtual bool IsClosing() = 0;

		// TODO: Required by GLAD, unsure if this is a good way to handle this
		virtual void* GetProcessAddress() = 0;

		inline unsigned int GetWidth() const { return s_Properties.Width; }
		inline unsigned int GetHeight() const { return s_Properties.Height; }

		inline static Window* Get() { return s_Instance; }

	protected:
		static WindowProperties s_Properties;
		static Window* s_Instance;
	};

	Window* CreateWindow();
}