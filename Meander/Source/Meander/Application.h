#pragma once
#include "ClientContext.h"

namespace Meander
{
	class Window;
	class RenderContext;

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run(ClientContext* context);
		void Exit();
		
		inline Window* GetWindow() { return m_Window; }
		inline RenderContext* GetRenderContext() { return m_RenderContext; }

		inline static Application* Get() { return s_Instance; }

	private:
		bool m_Running = false;
		Window* m_Window = nullptr;
		RenderContext* m_RenderContext = nullptr;

		static Application* s_Instance;
	};
}