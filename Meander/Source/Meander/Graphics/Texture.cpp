#include "pch.h"
#include "Texture.h"
#include "Meander/Graphics/RenderContext.h"
#include "Platform/OpenGL/GLTexture.h"

namespace Meander
{
	Texture* Texture::Create(const char* path)
	{
		switch (RenderContext::Get()->GetContextAPI())
		{
		case RenderContextAPI::OpenGL:
			return new GLTexture(path);
		}

		MN_ASSERT(false, "Unhandled graphics context.");
		return nullptr;
	}

	Texture* Texture::Create(uint32_t width, uint32_t height, unsigned char* pixels, const TextureFormat& format, const TextureDataType& dataType)
	{
		switch (RenderContext::Get()->GetContextAPI())
		{
		case RenderContextAPI::OpenGL:
			return new GLTexture(width, height, pixels, format, dataType);
		}

		MN_ASSERT(false, "Unhandled graphics context.");
		return nullptr;
	}
}