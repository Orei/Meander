#pragma once

namespace Meander
{
	class Application
	{
	public:
		virtual ~Application();

		void Run();
		void Exit();

		static Application* Create()
		{
			if (s_Instance != nullptr)
				return nullptr;

			return new Application();
		}

	private:
		Application();
		bool m_Running = false;

		static Application* s_Instance;
	};
}