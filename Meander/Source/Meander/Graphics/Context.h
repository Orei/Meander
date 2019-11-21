#pragma once

namespace Meander
{
	class Context
	{
	public:
		Context();
		virtual ~Context();

		virtual void Initialize() = 0;
		virtual void Clear() = 0;

		inline static Context* Get() { return s_Instance; }

	private:
		static Context* s_Instance;
	};

	Context* CreateContext();
}