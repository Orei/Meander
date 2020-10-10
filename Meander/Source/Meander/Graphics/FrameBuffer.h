#pragma once
#include "Texture.h"

namespace Meander
{
	class FrameBuffer
	{
	public:
		FrameBuffer() { }
		virtual ~FrameBuffer() { }
		
 		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void Resize(uint32_t width, uint32_t height) = 0;

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		Texture* GetColor() const { return m_Color; }
		Texture* GetDepth() const { return m_Depth; }

		static FrameBuffer* Create(uint32_t width, uint32_t height);

	protected:
		Texture* m_Color = nullptr;
		Texture* m_Depth = nullptr;
		uint32_t m_Width = 0;
		uint32_t m_Height = 0;
	};
}