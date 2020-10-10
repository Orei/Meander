#pragma once

namespace Meander
{
	class CubeMap
	{
	public:
		virtual void Bind(int slot = 0) const = 0;
		virtual void Unbind(int slot = 0) const = 0;

		static CubeMap* Create(const char** sixFacePaths);
	};
}