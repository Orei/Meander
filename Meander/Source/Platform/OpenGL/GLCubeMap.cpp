#include "pch.h"
#include "GLCubeMap.h"
#include <stb_image/stb_image.h>
#include <glad/glad.h>

namespace Meander
{
	GLCubeMap::GLCubeMap(const char** sixFacePaths)
	{
		glGenTextures(1, &m_Handle);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_Handle);

		stbi_set_flip_vertically_on_load(0);

		for (int i = 0; i < 6; i++)
		{
			int width;
			int height;
			int channels;
			unsigned char* pixels = stbi_load(sixFacePaths[i], &width, &height, &channels, STBI_rgb_alpha);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
			stbi_image_free(pixels);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	void GLCubeMap::Bind(int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_Handle);
	}

	void GLCubeMap::Unbind(int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
}