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
		Material(Shader* shader, Texture* diffuse = nullptr, Texture* normal = nullptr)
			: m_Shader(shader), m_Diffuse(diffuse), m_Normal(normal)
		{
		}

		void Bind() const;
		void Unbind() const;

		void SetShader(Shader* shader) { m_Shader = shader; }
		void SetDiffuse(Texture* diffuse) { m_Diffuse = diffuse; }
		void SetNormal(Texture* normal) { m_Normal = normal; }

		const Shader* GetShader() const { return m_Shader; }
		const Texture* GetDiffuse() const { return m_Diffuse; }
		const Texture* GetNormal() const { return m_Normal; }

	private:
		Shader* m_Shader = nullptr;
		Texture* m_Diffuse = nullptr;
		Texture* m_Normal = nullptr;
	};
}