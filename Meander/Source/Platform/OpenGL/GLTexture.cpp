#include "pch.h"
#include "GLTexture.h"
#include <stb_image/stb_image.h>
#include <glad/glad.h>

namespace Meander
{
	GLTexture::GLTexture(const char* path)
	{
		int width;
		int height;
		int channels;
		stbi_set_flip_vertically_on_load(1);
		unsigned char* pixels = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
		Generate(width, height, pixels);
		stbi_image_free(pixels);
	}

	GLTexture::GLTexture(unsigned int width, unsigned int height, unsigned char* pixels)
	{
		Generate(width, height, pixels);
	}

	void GLTexture::Bind(int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_Handle);
	}

	void GLTexture::Unbind(int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void GLTexture::Generate(unsigned int width, unsigned int height, unsigned char* pixels)
	{
		m_Width = width;
		m_Height = height;

		glGenTextures(1, &m_Handle);
		glBindTexture(GL_TEXTURE_2D, m_Handle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}