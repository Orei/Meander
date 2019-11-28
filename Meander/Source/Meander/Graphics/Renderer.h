#pragma once
#include <glm/mat4x4.hpp>

namespace Meander
{
	class Mesh;
	class Transform;
	class Material;
	class Context;

	class Renderer
	{
	public:
		static void Begin(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
		static void End();

		static void Render(const Transform& transform, const Shared<Mesh>& mesh, const Shared<Material>& material);

	protected:
		struct RenderData
		{
			Context* Context = nullptr;

			glm::mat4 ViewMatrix;
			glm::mat4 ProjectionMatrix;
		};

		static RenderData m_RenderData;
	};
}