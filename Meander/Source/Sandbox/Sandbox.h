#pragma once
#include "Meander/Application.h"

namespace Meander
{
	class Sandbox : public Application
	{
	public:
		virtual void Initialize() override;
		virtual void Load() override;
		virtual void Update(GameTime& gameTime) override;
		virtual void Render() override;
	};
}