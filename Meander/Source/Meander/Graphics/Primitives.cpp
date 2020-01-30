#include "pch.h"
#include "Primitives.h"

namespace Meander
{
	Shared<Mesh> Primitives::m_Quad = nullptr;
	Shared<Mesh> Primitives::m_Cube = nullptr;
	Shared<Mesh> Primitives::m_Plane = nullptr;
	BufferLayout Primitives::m_Layout;
}