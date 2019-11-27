#pragma once

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