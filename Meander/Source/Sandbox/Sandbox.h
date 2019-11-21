#pragma once
#include "Meander/Application.h"

namespace Meander
{
	class Sandbox : public Application
	{
	public:
		virtual void Initialize() override;
		virtual void Load() override;
		virtual void Update(float deltaTime) override;
		virtual void Render() override;
	};
}