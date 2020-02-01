#pragma once
#include <Meander/Application.h>

namespace Sandbox
{
	class Game : public Meander::Application
	{
	public:
		virtual void Initialize() override;
		virtual void Load() override;
		virtual void Update(Meander::GameTime& gameTime) override;
		virtual void Render() override;
	};
}