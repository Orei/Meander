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
		Both
	};

	/* Textures*/
	enum class TextureWrap
	{
		ClampEdge,
		ClampEdgeMirror,
		ClampBorder,
		Repeat,
		RepeatMirror
	};

	enum class TextureFormat
	{
		R,
		RG,
		RGB,
		RGBA,
		BGR,
		BGRA,

		//R_Int,
		//RG_Int,
		//RGB_Int,
		//BGR_Int,
		//BGRA_Int,

		StencilIndex,
		Depth,
		DepthStencil
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
		Double
	};
}