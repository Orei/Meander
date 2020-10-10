#pragma once
#include "Meander/Graphics/FrameBuffer.h"

namespace Meander
{
	class GLFrameBuffer : public FrameBuffer
	{
	public:
		GLFrameBuffer(uint32_t width, uint32_t height);
		virtual ~GLFrameBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void Resize(uint32_t width, uint32_t height) override;

	private:
		unsigned int m_Handle = 0;
	};
}