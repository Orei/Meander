#include "pch.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Context.h"
#include "Meander/Transform.h"
#include "Meander/Graphics/FrameBuffer.h"
#include "Lights.h"

namespace Meander
{
	Renderer::RenderData Renderer::m_RenderData;

	void Renderer::Begin(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
	{
		if (IsReady())
		{
			MN_WARN("Renderer::Begin has already been called, call Renderer::End first.");
			return;
		}

		m_RenderData.Context = Context::Get();
		m_RenderData.ViewMatrix = viewMatrix;
		m_RenderData.ProjectionMatrix = projectionMatrix;
	}

	void Renderer::End()
	{
		if (!IsReady())
		{
			MN_WARN("Renderer::Begin must be called before Renderer::End.");
			return;
		}

		m_RenderData.Context = nullptr;
		m_RenderData.ViewMatrix = glm::mat4(1.f);
		m_RenderData.ProjectionMatrix = glm::mat4(1.f);
	}

	void Renderer::SetRenderTarget(const Shared<FrameBuffer>& frameBuffer)
	{
		if (IsReady())
		{
			MN_WARN("Set render target before calling Renderer::Begin.");
			return;
		}

		if (m_RenderData.FrameBuffer != nullptr)
		{
			m_RenderData.FrameBuffer->Unbind();
			m_RenderData.FrameBuffer = nullptr;
		}

		if (frameBuffer == nullptr)
			return;

		m_RenderData.FrameBuffer = frameBuffer;
		m_RenderData.FrameBuffer->Bind();
	}

	void Renderer::Clear(const ClearFlags& flags)
	{
		if (!IsReady())
		{
			MN_WARN("Call Renderer::Begin before clearing.");
			return;
		}

		m_RenderData.Context->Clear(flags);
	}

	void Renderer::Render(const Transform& transform, const Shared<Mesh>& mesh, const Shared<Material>& material)
	{
		if (!IsReady())
		{
			MN_WARN("Call Renderer::Begin before rendering.");
			return;
		}

		material->GetShader()->Set("u_Projection", m_RenderData.ProjectionMatrix);
		material->GetShader()->Set("u_View", m_RenderData.ViewMatrix);
		material->GetShader()->Set("u_Model", transform.GetMatrix());

		material->Bind();
		m_RenderData.Context->Render(mesh->GetVertexArray());
		material->Unbind();
	}

	void Renderer::Render(const Shared<FrameBuffer>& frameBuffer, const Shared<Shader>& shader)
	{
		if (!IsReady())
		{
			MN_WARN("Call Renderer::Begin before rendering.");
			return;
		}

		shader->Set("u_Color", COLOR_BUFFER_SLOT);
		shader->Set("u_Depth", DEPTH_BUFFER_SLOT);

		shader->Bind();
		frameBuffer->GetColor()->Bind(COLOR_BUFFER_SLOT);
		frameBuffer->GetDepth()->Bind(DEPTH_BUFFER_SLOT);
		m_RenderData.Context->FillScreen();
		frameBuffer->GetDepth()->Unbind(DEPTH_BUFFER_SLOT);
		frameBuffer->GetColor()->Unbind(COLOR_BUFFER_SLOT);
		shader->Unbind();
	}
}