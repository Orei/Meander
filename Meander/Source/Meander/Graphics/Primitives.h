#pragma once

namespace Meander
{
	class Mesh;
	class BufferLayout;

	class Primitives
	{
	public:
		/* Generates the primitive meshes. */
		static void Initialize();

		/* Generates and returns a new unit rows-by-columns plane. */
		static Mesh* GeneratePlane(int rows, int columns);

		/* Returns a unit-quad mesh. */
		static Mesh* GetQuad() { return s_Quad; }

		/* Returns a unit-cube mesh. */
		static Mesh* GetCube() { return s_Cube; }

		/* Returns a unit 10-by-10-plane. */
		static Mesh* GetPlane() { return s_Plane; }

	private:
		static Mesh* s_Quad;
		static Mesh* s_Cube;
		static Mesh* s_Plane;
		static BufferLayout s_Layout;
	};
}