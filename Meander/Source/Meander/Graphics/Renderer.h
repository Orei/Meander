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
	class CubeMap;
	class DirectionalLight;
	enum class ClearFlags;

	class Renderer
	{
	public:
		/* Must be called prior to rendering. */
		static void Begin(const glm::mat4& viewMatrix = glm::mat4(1.f), const glm::mat4& projectionMatrix = glm::mat4(1.f));

		/* Must be called after rendering. */
		static void End();

		/* Set the active framebuffer which will be rendered to. Use a nullptr to reset to default framebuffer. */
		static void SetRenderTarget(const Shared<FrameBuffer>& frameBuffer);

		/* Clears the active framebuffer. */
		static void Clear(const ClearFlags& flags);

		/* Renders a mesh. */
		static void Render(const Transform& transform, const Shared<Mesh>& mesh, const Shared<Material>& material);
		
		/* Renders a framebuffer. */
		static void Render(const Shared<FrameBuffer>& frameBuffer, const Shared<Shader>& shader);

		/* Checks whether the renderer has begun. */
		static bool IsReady() { return m_RenderData.Context != nullptr; }

	protected:
		struct RenderData
		{
			Context* Context = nullptr;

			glm::mat4 ViewMatrix;
			glm::mat4 ProjectionMatrix;

			Shared<FrameBuffer> FrameBuffer;
		};

		static RenderData m_RenderData;
	};
}