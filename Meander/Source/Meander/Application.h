#pragma once
#include "GameTime.h"

namespace Meander
{
	class Window;
	class Context;

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void Exit();

		virtual void Initialize() = 0;
		virtual void Load() = 0;
		virtual void Update(GameTime& gameTime) = 0;
		virtual void Render(GameTime& gameTime) = 0;
		virtual void OnGui(GameTime& gameTime) = 0;

	protected:
		Window* m_Window = nullptr;
		Context* m_Context = nullptr;

	private:
		bool m_Running = false;

		static Application* s_Instance;
	};
}