#include "pch.h"
#include "GLTypes.h"
#include <glad/glad.h>

namespace Meander
{
	uint32_t GLTypes::GetClearFlags(const ClearFlags& flags)
	{
		int value = 0;

		if ((int)flags & (int)ClearFlags::Depth)
			value += GL_DEPTH_BUFFER_BIT;

		if ((int)flags & (int)ClearFlags::Color)
			value += GL_COLOR_BUFFER_BIT;

		if ((int)flags & (int)ClearFlags::Stencil)
			value += GL_STENCIL_BUFFER_BIT;

		return value;
	}

	uint32_t GLTypes::GetTextureFormat(const TextureFormat& format)
	{
		switch (format)
		{
		case TextureFormat::R: return GL_RED;
		case TextureFormat::RG: return GL_RG;
		case TextureFormat::RGB: return GL_RGB;
		case TextureFormat::RGBA: return GL_RGBA;
		case TextureFormat::BGR: return GL_BGR;
		case TextureFormat::BGRA: return GL_BGRA;
		case TextureFormat::Depth: return GL_DEPTH_COMPONENT;
		case TextureFormat::DepthStencil: return GL_DEPTH_STENCIL;
		case TextureFormat::StencilIndex: return GL_STENCIL_INDEX;
		}

		MN_ASSERT(false, "Unknown texture format.");
		return 0;
	}

	uint32_t GLTypes::GetWindingOrder(const WindingOrder& order)
	{
		switch (order)
		{
		case WindingOrder::Clockwise: return GL_CW;
		case WindingOrder::CounterClockwise: return GL_CCW;
		}

		MN_ASSERT(false, "Unknown winding order.");
		return 0;
	}

	uint32_t GLTypes::GetCullDirection(const CullDirection& direction)
	{
		switch (direction)
		{
		case CullDirection::Front: return GL_FRONT;
		case CullDirection::Back: return GL_BACK;
		case CullDirection::Both: return GL_FRONT_AND_BACK;
		}

		MN_ASSERT(false, "Unknown culling direction.");
		return 0;
	}

	uint32_t GLTypes::GetTextureWrap(const TextureWrap& wrap)
	{
		switch (wrap)
		{
		case TextureWrap::ClampBorder: return GL_CLAMP_TO_BORDER;
		case TextureWrap::ClampEdge: return GL_CLAMP_TO_EDGE;
		case TextureWrap::ClampEdgeMirror: return GL_MIRROR_CLAMP_TO_EDGE; 
		case TextureWrap::Repeat: return GL_REPEAT;
		case TextureWrap::RepeatMirror: return GL_MIRRORED_REPEAT; 
		}

		MN_ASSERT(false, "Unknown texture wrap mode.");
		return 0;
	}

	uint32_t GLTypes::GetTextureDataType(const TextureDataType& type)
	{
		switch (type)
		{
		case TextureDataType::Byte: return GL_BYTE;
		case TextureDataType::UByte: return GL_UNSIGNED_BYTE;
		case TextureDataType::Short: return GL_SHORT;
		case TextureDataType::UShort: return GL_UNSIGNED_SHORT;
		case TextureDataType::Int: return GL_INT;
		case TextureDataType::UInt: return GL_UNSIGNED_INT;
		case TextureDataType::Float: return GL_FLOAT;
		case TextureDataType::Double: return GL_DOUBLE;
		}

		MN_ASSERT(false, "Unknown texture data type.");
		return 0;
	}
}