#pragma once
#include "Meander/Graphics/CubeMap.h"

namespace Meander
{
	class GLCubeMap : public CubeMap
	{
	public:
		GLCubeMap(const char** sixFacePaths);

		virtual void Bind(int slot = 0) const override;
		virtual void Unbind(int slot = 0) const override;

	private:
		uint32_t m_Handle = 0;
	};
}