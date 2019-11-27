#pragma once
#include "Meander/Common.h"

namespace Meander
{
	class Shader;
	class Texture;

	class Material
	{
	public:
		Material() { }
		Material(Shared<Shader> shader, Shared<Texture> diffuse = nullptr, Shared<Texture> normal = nullptr)
			: m_Shader(shader), m_Diffuse(diffuse), m_Normal(normal)
		{
		}

		void Bind() const;
		void Unbind() const;

		void SetShader(Shared<Shader> shader) { m_Shader = shader; }
		void SetDiffuse(Shared<Texture> diffuse) { m_Diffuse = diffuse; }
		void SetNormal(Shared<Texture> normal) { m_Normal = normal; }

		const Shared<Shader>& GetShader() const { return m_Shader; }
		const Shared<Texture>& GetDiffuse() const { return m_Diffuse; }
		const Shared<Texture>& GetNormal() const { return m_Normal; }

	private:
		Shared<Shader> m_Shader = nullptr;
		Shared<Texture> m_Diffuse = nullptr;
		Shared<Texture> m_Normal = nullptr;
	};
}