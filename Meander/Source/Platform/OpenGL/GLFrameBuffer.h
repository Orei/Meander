#pragma once
#include "Meander/Graphics/FrameBuffer.h"

namespace Meander
{
	class GLFrameBuffer : public FrameBuffer
	{
	public:
		GLFrameBuffer(unsigned int width, unsigned int height);
		~GLFrameBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:
		unsigned int m_Handle = 0;
	};
}