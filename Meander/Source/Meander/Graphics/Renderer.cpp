#include "pch.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Context.h"
#include "Meander/Transform.h"

namespace Meander
{
	Renderer::RenderData Renderer::m_RenderData;

	void Renderer::Begin(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
	{
		m_RenderData.Context = Context::Get();
		m_RenderData.ViewMatrix = viewMatrix;
		m_RenderData.ProjectionMatrix = projectionMatrix;
	}

	void Renderer::End()
	{
		m_RenderData.Context = nullptr;
	}

	void Renderer::Render(const Transform& transform, const Shared<Mesh>& mesh, const Shared<Material>& material)
	{
		material->GetShader()->Set("u_View", m_RenderData.ViewMatrix);
		material->GetShader()->Set("u_Projection", m_RenderData.ProjectionMatrix);
		material->GetShader()->Set("u_Transform", transform.GetMatrix());

		material->Bind();
		m_RenderData.Context->Render(mesh->GetVertexArray());
		material->Unbind();
	}
}