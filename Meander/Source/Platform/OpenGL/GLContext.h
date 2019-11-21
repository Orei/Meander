#pragma once
#include "Meander/Graphics/Context.h"

namespace Meander
{
	class GLContext : public Context
	{
	public:
		virtual void Initialize() override;
		virtual void Clear() override;
	};
}