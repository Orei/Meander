#include "pch.h"
#include "GLTypes.h"

/* TODO: Should consider using GL's definitions directly (i.e GL_FRONT, GL_RGBA etc), rather than hard-copying their values. */

namespace Meander
{
	// TODO: Very temporary, needed a quick fix; also, how do I convert flags efficiently?
	unsigned int GLTypes::GetClearFlags(const ClearFlags& flags)
	{
		int value = static_cast<int>(flags);

		switch (value)
		{
		case 1 << 0: return 0x00000100;
		case 1 << 1: return 0x00004000;
		case (1 << 0 + 1 << 1): return 0x00000100 + 0x00004000;
		}

		return value;
	}

	unsigned int GLTypes::GetTextureFormat(const TextureFormat& format)
	{
		switch (format)
		{
		case TextureFormat::RGB: return 0x1907;
		case TextureFormat::RGBA: return 0x1908;
		case TextureFormat::Luminance: return 0x1909;
		case TextureFormat::LuminanceAlpha: return 0x190A;
		case TextureFormat::Depth: return 0x1902;
		case TextureFormat::Depth16: return 0x81A5;
		case TextureFormat::Depth24: return 0x81A6;
		case TextureFormat::Depth32: return 0x81A7;
		}

		MN_ASSERT(false, "Unknown texture format.");
		return 0;
	}

	unsigned int GLTypes::GetWindingOrder(const WindingOrder& order)
	{
		switch (order)
		{
		case WindingOrder::CounterClockwise: return 0x0900;
		case WindingOrder::Clockwise: return 0x0901;
		}

		MN_ASSERT(false, "Unknown winding order.");
		return 0;
	}

	unsigned int GLTypes::GetCullDirection(const CullDirection& direction)
	{
		switch (direction)
		{
		case CullDirection::Back: return 0x0404;
		case CullDirection::Front: return 0x0405;
		case CullDirection::All: return 0x0408;
		}

		MN_ASSERT(false, "Unknown culling direction.");
		return 0;
	}

	unsigned int GLTypes::GetTextureWrap(const TextureWrap& wrap)
	{
		switch (wrap)
		{
		case TextureWrap::Clamp: return 0x2900;
		case TextureWrap::ClampBorder: return 0x812F;
		case TextureWrap::ClampEdge: return 0x812D;
		case TextureWrap::Repeat: return 0x2901;
		case TextureWrap::RepeatMirror: return 0x8370;
		}

		MN_ASSERT(false, "Unknown texture wrap mode.");
		return 0;
	}

	unsigned int GLTypes::GetTextureDataType(const TextureDataType& type)
	{
		switch (type)
		{
		case TextureDataType::Byte: return 0x1400;
		case TextureDataType::UByte: return 0x1401;
		case TextureDataType::Short: return 0x1402;
		case TextureDataType::UShort: return 0x1403;
		case TextureDataType::Int: return 0x1404;
		case TextureDataType::UInt: return 0x1405;
		case TextureDataType::Float: return 0x1406;
		case TextureDataType::Byte2: return 0x1407;
		case TextureDataType::Byte3: return 0x1408;
		case TextureDataType::Byte4: return 0x1409;
		case TextureDataType::Double: return 0x140A;
		}

		MN_ASSERT(false, "Unknown texture data type.");
		return 0;
	}
}