#include "pch.h"
#include "Texture.h"
#include "Meander/Graphics/Context.h"
#include "Platform/OpenGL/GLTexture.h"

namespace Meander
{
	Texture* Texture::Create(const char* path)
	{
		switch (Context::Get()->GetContextAPI())
		{
		case ContextAPI::OpenGL:
			return new GLTexture(path);
		}

		MN_ASSERT(false, "Unhandled graphics context.");
		return nullptr;
	}

	Texture* Texture::Create(unsigned int width, unsigned int height, unsigned char* pixels, const TextureFormat& format, const TextureDataType& dataType)
	{
		switch (Context::Get()->GetContextAPI())
		{
		case ContextAPI::OpenGL:
			return new GLTexture(width, height, pixels, format, dataType);
		}

		MN_ASSERT(false, "Unhandled graphics context.");
		return nullptr;
	}
}