#pragma once
#include <glm/vec4.hpp>

namespace Meander
{
	enum class ClearFlags : int
	{
		Depth = 0x00000100,
		Color = 0x00004000
	};

	inline ClearFlags operator|(ClearFlags a, ClearFlags b)
	{
		return static_cast<ClearFlags>(static_cast<int>(a) | static_cast<int>(b));
	}

	enum class ContextAPI
	{
		OpenGL
	};

	class VertexArray;

	class Context
	{
	public:
		Context();
		virtual ~Context();

		/* Initializes the graphics context. */
		virtual void Initialize() = 0;

		/* Enables a capability, should be used when a specific function is not yet added to the context. */
		virtual void Enable(unsigned int capabilities) = 0;

		/* Disables a capability, should be used when a specific function is not yet added to the context. */
		virtual void Disable(unsigned int capabilities) = 0;

		/* Sets the clear-color. */
		virtual void SetClearColor(const glm::vec4& color) = 0;

		/* Enables or disables depth-testing. */
		virtual void SetDepthTest(bool enabled) = 0;

		/* Clears the specified buffers. */
		virtual void Clear(const ClearFlags& flags) = 0;

		/* Renders a mesh. */
		virtual void Render(const Shared<VertexArray>& vertexArray) = 0;

		/* Returns the Context API. */
		virtual const ContextAPI& GetContextAPI() const = 0;

		/* Returns the context instance. */
		inline static Context* Get() { return s_Instance; }

	private:
		static Context* s_Instance;
	};

	Context* CreateContext();
}