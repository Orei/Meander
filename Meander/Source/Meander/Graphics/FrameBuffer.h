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

		const Shared<Texture>& GetColor() const { return m_Color; }
		const Shared<Texture>& GetDepth() const { return m_Depth; }

		static Shared<FrameBuffer> Create(unsigned int width, unsigned int height);

	protected:
		Shared<Texture> m_Color = nullptr;
		Shared<Texture> m_Depth = nullptr;
		unsigned int m_Width = 0;
		unsigned int m_Height = 0;
	};
}