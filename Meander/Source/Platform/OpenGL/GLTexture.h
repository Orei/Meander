#pragma once
#include "Meander/Graphics/Texture.h"

namespace Meander
{
	class GLTexture : public Texture
	{
	public:
		GLTexture(const char* path);
		GLTexture(uint32_t width, uint32_t height, unsigned char* pixels, const TextureFormat& format, const TextureDataType& dataType);
		~GLTexture();

		virtual void Bind(int slot = 0) const override;
		virtual void Unbind(int slot = 0) const override;

		uint32_t GetHandle() const { return m_Handle; }

	private:
		uint32_t m_Handle = 0;

		void Generate(uint32_t width, uint32_t height, unsigned char* pixels, const TextureFormat& format, const TextureDataType& dataType);
	};
}