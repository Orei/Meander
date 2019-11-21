#include "pch.h"
#include "Context.h"

namespace Meander
{
	Context* Context::s_Instance = nullptr;

	Context::Context()
	{
		MN_ASSERT(s_Instance == nullptr, "An instance of Context already exists.");

		s_Instance = this;
	}

	Context::~Context()
	{
		s_Instance = nullptr;
	}
}