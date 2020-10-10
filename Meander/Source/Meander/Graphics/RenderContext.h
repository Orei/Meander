#pragma once
#include "Types.h"
#include <glm/vec4.hpp>

namespace Meander
{
	enum class RenderContextAPI
	{
		OpenGL
	};

	class VertexArray;

	class RenderContext
	{
	public:
		RenderContext();
		virtual ~RenderContext();

		/* Initializes the graphics context. */
		virtual void Initialize() = 0;

		/* Enables a capability, should be used when a specific function is not yet added to the context. */
		virtual void Enable(uint32_t capabilities) = 0;

		/* Disables a capability, should be used when a specific function is not yet added to the context. */
		virtual void Disable(uint32_t capabilities) = 0;

		/* Sets the clear-color. */
		virtual void SetClearColor(const glm::vec4& color) = 0;

		/* Enables or disables depth-testing. */
		virtual void SetDepthTest(bool enabled) = 0;

		/* Enables or disables blending. */
		virtual void SetBlend(bool enabled) = 0;

		/* Enables or disables face culling. */
		virtual void SetCullFace(bool enabled) = 0;

		/* Sets front-face winding order. */
		virtual void SetWindingOrder(const WindingOrder& order) = 0;

		/* Sets face culling direction. */
		virtual void SetCullDirection(const CullDirection& direction) = 0;

		/* Clears the specified buffers. */
		virtual void Clear(const ClearFlags& flags) = 0;

		/* Renders a vertex array. */
		virtual void Render(const VertexArray* vertexArray) = 0;

		/* Renders a full-screen quad, mainly used to render framebuffers to the screen. */
		virtual void FillScreen() = 0;

		/* Returns the context API. */
		virtual const RenderContextAPI& GetContextAPI() const = 0;

		/* Returns the context instance. */
		inline static RenderContext* Get() { return s_Instance; }

	private:
		static RenderContext* s_Instance;
	};
}