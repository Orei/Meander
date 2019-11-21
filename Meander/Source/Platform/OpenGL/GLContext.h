#pragma once
#include "Meander/Graphics/Context.h"

namespace Meander
{
	class GLContext : public Context
	{
	public:
		/* Initializes the graphics context. */
		virtual void Initialize() override;

		/* Enables a capability, should be used when a specific function is not yet added to the context. */
		virtual void Enable(unsigned int capabilities) override;

		/* Disables a capability, should be used when a specific function is not yet added to the context. */
		virtual void Disable(unsigned int capabilities) override;
		
		/* Sets the clear-color. */
		virtual void SetClearColor(const glm::vec4& color) override;

		/* Clears the specified buffers. */
		virtual void Clear(ClearFlags flags) override;
	};
}