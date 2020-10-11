#pragma once
#include "Meander/Graphics/Types.h"

namespace Meander
{
	class GLTypes
	{
	public:
		static uint32_t GetClearFlags(const ClearFlags& flags);
		static uint32_t GetTextureFormat(const TextureFormat& format);
		static uint32_t GetWindingOrder(const WindingOrder& order);
		static uint32_t GetCullDirection(const CullDirection& direction);
		static uint32_t GetTextureWrap(const TextureWrap& wrap);
		static uint32_t GetTextureDataType(const TextureDataType& type);
	};
}