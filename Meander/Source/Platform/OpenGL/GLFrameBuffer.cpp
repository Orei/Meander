#include "pch.h"
#include "GLFrameBuffer.h"
#include "GLTexture.h"
#include "Meander/Window.h"
#include <glad/glad.h>

namespace Meander
{
	GLFrameBuffer::GLFrameBuffer(unsigned int width, unsigned int height)
	{
		m_Width = width;
		m_Height = height;

		glGenFramebuffers(1, &m_Handle);
		glBindFramebuffer(GL_FRAMEBUFFER, m_Handle);

		m_Color = Texture::Create(m_Width, m_Height, nullptr, TextureFormat::RGBA, TextureDataType::UByte);
		m_Depth = Texture::Create(m_Width, m_Height, nullptr, TextureFormat::Depth, TextureDataType::Float);

		// NOTE: We have to cast to GLTexture in order to get the handle, is there a better way to do this?
		// It only happens once on construction though, so it shouldn't cause issues
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, std::static_pointer_cast<GLTexture>(m_Color)->GetHandle(), 0);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, std::static_pointer_cast<GLTexture>(m_Depth)->GetHandle(), 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	GLFrameBuffer::~GLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_Handle);
	}

	void GLFrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_Handle);
		glViewport(0, 0, m_Width, m_Height);
	}

	void GLFrameBuffer::Unbind() const
	{
		// TODO: Figure out a better way to do this
		Window* window = Window::Get();
		unsigned int width = window->GetWidth();
		unsigned int height = window->GetHeight();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, width, height);
	}
}