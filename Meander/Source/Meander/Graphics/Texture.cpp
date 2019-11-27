#include "pch.h"
#include "Texture.h"
#include "Meander/Graphics/Context.h"
#include "Platform/OpenGL/GLTexture.h"

namespace Meander
{
	Shared<Texture> Texture::Create(const char* path)
	{
		switch (Context::Get()->GetContextAPI())
		{
		case ContextAPI::OpenGL:
			return CreateShared<GLTexture>(path);
		}

		MN_ASSERT(false, "Unhandled graphics context.");
		return nullptr;
	}

	Shared<Texture> Texture::Create(unsigned int width, unsigned int height, unsigned char* pixels)
	{
		switch (Context::Get()->GetContextAPI())
		{
		case ContextAPI::OpenGL:
			return CreateShared<GLTexture>(width, height, pixels);
		}

		MN_ASSERT(false, "Unhandled graphics context.");
		return nullptr;
	}
}