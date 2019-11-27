#pragma once
#include "Meander/Common.h"

namespace Meander
{
	class Texture
	{
	public:
		/* Binds the texture to the specified slot. */
		virtual void Bind(int slot = 0) const = 0;

		/* Unbinds the texture of the specified slot. */
		virtual void Unbind(int slot = 0) const = 0;

		/* Returns the width of the texture. */
		unsigned int GetWidth() const { return m_Width; }

		/* Returns the height of the texture. */
		unsigned int GetHeight() const { return m_Height; }

		static Shared<Texture> Create(const char* path);
		static Shared<Texture> Create(unsigned int width, unsigned int height, unsigned char* pixels);

	protected:
		unsigned int m_Width = 0;
		unsigned int m_Height = 0;
	};
}