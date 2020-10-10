#pragma once
#include "Meander/Graphics/Types.h"

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
		uint32_t GetWidth() const { return m_Width; }

		/* Returns the height of the texture. */
		uint32_t GetHeight() const { return m_Height; }

		static Texture* Create(const char* path);
		static Texture* Create(uint32_t width, uint32_t height, unsigned char* pixels, const TextureFormat& format = TextureFormat::RGBA,
			const TextureDataType& dataType = TextureDataType::UByte);

	protected:
		uint32_t m_Width = 0;
		uint32_t m_Height = 0;
	};
}