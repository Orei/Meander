#pragma once
#include "Renderer.h"

namespace Meander
{
	class ForwardRenderer : public Renderer
	{
	protected:
		virtual void Sort() override;
	};
}