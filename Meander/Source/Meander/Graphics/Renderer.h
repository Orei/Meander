#pragma once
#include <glm/mat4x4.hpp>

namespace Meander
{
	class Mesh;
	class Transform;
	class Material;
	class Context;
	class FrameBuffer;
	class Shader;
	enum class ClearFlags;

	class Renderer
	{
	public:
		/* Must be called pre-rendering. */
		static void Begin();

		/* Must be called pre-rendering. */
		static void Begin(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

		/* Must be called post-rendering. */
		static void End();

		/* Set the active framebuffer which will be rendered to. Use a nullptr to reset to default framebuffer. */
		static void SetRenderTarget(const Shared<FrameBuffer>& frameBuffer);

		/* Clears the active framebuffer. */
		static void Clear(const ClearFlags& flags);

		/* Renders a mesh. */
		static void Render(const Transform& transform, const Shared<Mesh>& mesh, const Shared<Material>& material);
		
		/* Renders a framebuffer. */
		static void Render(const Shared<FrameBuffer>& frameBuffer, const Shared<Shader>& shader);

	protected:
		struct RenderData
		{
			Context* Context = nullptr;

			glm::mat4 ViewMatrix;
			glm::mat4 ProjectionMatrix;

			Shared<FrameBuffer> FrameBuffer;
		};

		static RenderData m_RenderData;
		static bool m_HasBegun;
	};
}