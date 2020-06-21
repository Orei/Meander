#include "pch.h"
#include "RenderContext.h"

namespace Meander
{
	RenderContext* RenderContext::s_Instance = nullptr;

	RenderContext::RenderContext()
	{
		MN_ASSERT(s_Instance == nullptr, "An instance of RenderContext already exists.");
		s_Instance = this;
	}

	RenderContext::~RenderContext()
	{
		s_Instance = nullptr;
	}
}