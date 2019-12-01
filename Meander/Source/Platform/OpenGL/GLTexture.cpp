#include "pch.h"
#include "GLTexture.h"
#include "Platform/OpenGL/GLTypes.h"
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
		Generate(width, height, pixels, TextureFormat::RGBA, TextureDataType::UByte);
		stbi_image_free(pixels);
	}

	GLTexture::GLTexture(unsigned int width, unsigned int height, unsigned char* pixels, const TextureFormat& format,
		const TextureDataType& dataType)
	{
		Generate(width, height, pixels, format, dataType);
	}

	GLTexture::~GLTexture()
	{
		glDeleteTextures(1, &m_Handle);
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

	// NOTE: Construct proxy, we don't really want to copy-paste this, but it should be accessible from all constructors
	void GLTexture::Generate(unsigned int width, unsigned int height, unsigned char* pixels, const TextureFormat& format, 
		const TextureDataType& dataType)
	{
		m_Width = width;
		m_Height = height;

		glGenTextures(1, &m_Handle);
		glBindTexture(GL_TEXTURE_2D, m_Handle);
		glTexImage2D(GL_TEXTURE_2D, 0, GLTypes::GetTextureFormat(format), m_Width, m_Height, 0, GLTypes::GetTextureFormat(format),
			GLTypes::GetTextureDataType(dataType), pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}