#include "pch.h"
#include "CubeMap.h"
#include "Meander/Graphics/Context.h"
#include "Platform/OpenGL/GLCubeMap.h"

namespace Meander
{
	CubeMap* CubeMap::Create(const char** sixFacePaths)
	{
		switch (Context::Get()->GetContextAPI())
		{
		case ContextAPI::OpenGL:
			return new GLCubeMap(sixFacePaths);
		}

		MN_ASSERT(false, "Unhandled graphics context.");
		return nullptr;
	}
}
