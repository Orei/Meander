#pragma once
#include "Client.h"
#include "WindowProperties.h"

namespace Meander
{
	class Window;
	class RenderContext;
	class Canvas;

	class Application
	{
	public:
		Application(const WindowProperties& windowProperties = WindowProperties());
		virtual ~Application();

		void Run(Client* context);
		void Exit();
		
		inline Window* GetWindow() { return m_Window; }
		inline RenderContext* GetRenderContext() { return m_RenderContext; }
		inline Canvas* GetCanvas() { return m_Canvas; }

		inline static Application* Get() { return s_Instance; }

	private:
		bool m_Running = false;
		Window* m_Window = nullptr;
		RenderContext* m_RenderContext = nullptr;
		Canvas* m_Canvas = nullptr;

		static Application* s_Instance;
	};
}
