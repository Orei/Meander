#pragma once
#include "Texture.h"

namespace Meander
{
	class FrameBuffer
	{
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

		Texture* GetColor() const { return m_Color; }
		Texture* GetDepth() const { return m_Depth; }

		static FrameBuffer* Create(unsigned int width, unsigned int height);

	protected:
		Texture* m_Color = nullptr;
		Texture* m_Depth = nullptr;
		unsigned int m_Width = 0;
		unsigned int m_Height = 0;
	};
}