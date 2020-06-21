#include "pch.h"
#include "CubeMap.h"
#include "Meander/Graphics/RenderContext.h"
#include "Platform/OpenGL/GLCubeMap.h"

namespace Meander
{
	CubeMap* CubeMap::Create(const char** sixFacePaths)
	{
		switch (RenderContext::Get()->GetContextAPI())
		{
		case RenderContextAPI::OpenGL:
			return new GLCubeMap(sixFacePaths);
		}

		MN_ASSERT(false, "Unhandled graphics context.");
		return nullptr;
	}
}
