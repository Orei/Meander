#include "pch.h"
#include "CubeMap.h"
#include "Meander/Graphics/Context.h"
#include "Platform/OpenGL/GLCubeMap.h"

namespace Meander
{
	Shared<CubeMap> CubeMap::Create(const char** sixFacePaths)
	{
		switch (Context::Get()->GetContextAPI())
		{
		case ContextAPI::OpenGL:
			return CreateShared<GLCubeMap>(sixFacePaths);
		}

		MN_ASSERT(false, "Unhandled graphics context.");
		return nullptr;
	}
}
