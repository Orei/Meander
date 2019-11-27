#pragma once
#include "Meander/Graphics/Texture.h"

namespace Meander
{
	class GLTexture : public Texture
	{
	public:
		GLTexture(const char* path);
		GLTexture(unsigned int width, unsigned int height, unsigned char* pixels);

		virtual void Bind(int slot = 0) const override;
		virtual void Unbind(int slot = 0) const override;

	private:
		unsigned int m_Handle = 0;

		void Generate(unsigned int width, unsigned int height, unsigned char* pixels = nullptr);
	};
}