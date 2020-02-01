#pragma once
#include "Meander/Graphics/Types.h"

namespace Meander
{
	class GLTypes
	{
	public:
		static unsigned int GetClearFlags(const ClearFlags& flags);
		static unsigned int GetTextureFormat(const TextureFormat& format);
		static unsigned int GetWindingOrder(const WindingOrder& order);
		static unsigned int GetCullDirection(const CullDirection& direction);
		static unsigned int GetTextureWrap(const TextureWrap& wrap);
		static unsigned int GetTextureDataType(const TextureDataType& type);
	};
}