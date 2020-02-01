#pragma once

namespace Meander
{
	/* Flags */
	enum class ClearFlags : int
	{
		Depth = 1 << 0,
		Color = 1 << 1
	};

	inline ClearFlags operator|(ClearFlags a, ClearFlags b)
	{
		return static_cast<ClearFlags>(static_cast<int>(a) | static_cast<int>(b));
	}

	/* Faces */
	enum class WindingOrder
	{
		CounterClockwise,
		Clockwise
	};

	enum class CullDirection
	{
		Back,
		Front,
		All
	};

	/* Textures*/
	enum class TextureWrap
	{
		Clamp,
		ClampEdge,
		ClampBorder,
		Repeat,
		RepeatMirror
	};

	enum class TextureFormat
	{
		RGB,
		RGBA,
		Luminance,
		LuminanceAlpha,
		Depth,
		Depth16,
		Depth24,
		Depth32,
	};

	enum class TextureDataType
	{
		Byte,
		UByte,
		Short,
		UShort,
		Int,
		UInt,
		Float,
		Byte2,
		Byte3,
		Byte4,
		Double
	};
}