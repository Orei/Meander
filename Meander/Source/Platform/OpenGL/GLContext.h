#pragma once
#include "Meander/Graphics/RenderContext.h"

namespace Meander
{
	class GLContext : public RenderContext
	{
	public:
		/* Initializes the graphics context. */
		virtual void Initialize() override;

		/* Enables a capability, should be used when a specific function is not yet added to the context. */
		virtual void Enable(uint32_t capabilities) override;

		/* Disables a capability, should be used when a specific function is not yet added to the context. */
		virtual void Disable(uint32_t capabilities) override;
		
		/* Sets the clear-color. */
		virtual void SetClearColor(const glm::vec4& color) override;

		/* Enables or disables depth-testing. */
		virtual void SetDepthTest(bool enabled) override;

		/* Enables or disables blending. */
		virtual void SetBlend(bool enabled) override;

		/* Enables or disables face culling. */
		virtual void SetCullFace(bool enabled) override;

		/* Sets front-face winding order. */
		virtual void SetWindingOrder(const WindingOrder& order) override;

		/* Sets face culling direction. */
		virtual void SetCullDirection(const CullDirection& direction) override;

		/* Clears the specified buffers. */
		virtual void Clear(const ClearFlags& flags) override;

		/* Renders a vertex array. */
		virtual void Render(const VertexArray* vertexArray) override;
		
		/* Renders a full-screen quad, mainly used to render framebuffers to the screen. */
		virtual void FillScreen() override;

		/* Returns the Context API, OpenGL in this case. */
		virtual const RenderContextAPI& GetContextAPI() const override { return m_API; }

	private:
		RenderContextAPI m_API = RenderContextAPI::OpenGL;
	};
}