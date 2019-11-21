#pragma once

namespace Meander
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void Exit();

		virtual void Initialize() = 0;
		virtual void Load() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;

	private:
		bool m_Running = false;

		static Application* s_Instance;
	};

	// Defined in Sandbox, should remain undefined if exported.
	Application* CreateApplication();
}