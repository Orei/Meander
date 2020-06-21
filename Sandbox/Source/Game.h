#pragma once
#include <Meander/ClientContext.h>

namespace Sandbox
{
	class Game : public Meander::ClientContext
	{
	protected:
		virtual void Initialize() override;
		virtual void Load() override;
		virtual void Update(Meander::GameTime& gameTime) override;
		virtual void Render(Meander::GameTime& gameTime) override;
		virtual void RenderUI(Meander::GameTime& gameTime) override;
	};
}