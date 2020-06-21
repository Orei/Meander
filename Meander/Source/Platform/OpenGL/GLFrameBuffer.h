#pragma once
#include "Meander/Graphics/FrameBuffer.h"

namespace Meander
{
	class GLFrameBuffer : public FrameBuffer
	{
	public:
		GLFrameBuffer(unsigned int width, unsigned int height);
		virtual ~GLFrameBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void Resize(unsigned int width, unsigned int height) override;

	private:
		unsigned int m_Handle = 0;
	};
}