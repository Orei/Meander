#include "pch.h"
#include "Material.h"
#include "Texture.h"
#include "Shader.h"

namespace Meander
{
	void Material::Bind() const
	{
		if (m_Diffuse != nullptr)
			m_Diffuse->Bind(DIFFUSE_SLOT);

		if (m_Normal != nullptr)
			m_Normal->Bind(NORMAL_SLOT);

		m_Shader->Set("u_Material.Diffuse", DIFFUSE_SLOT);
		m_Shader->Set("u_Material.Normal", NORMAL_SLOT);
		m_Shader->Set("u_Material.HasDiffuse", m_Diffuse != nullptr);
		m_Shader->Set("u_Material.HasNormal", m_Normal != nullptr);
		m_Shader->Bind();
	}

	void Material::Unbind() const
	{
		if (m_Diffuse != nullptr)
			m_Diffuse->Unbind(DIFFUSE_SLOT);

		if (m_Normal != nullptr)
			m_Normal->Unbind(NORMAL_SLOT);

		m_Shader->Unbind();
	}
}