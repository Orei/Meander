#include "pch.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "RenderContext.h"
#include "Meander/Transform.h"
#include "Meander/Graphics/FrameBuffer.h"

namespace Meander
{
	void Renderer::Begin(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
	{
		if (HasBegun())
		{
			MN_WARN("Renderer::Begin has already been called, call Renderer::End first.");
			return;
		}

		m_RenderData.Context = RenderContext::Get();
		m_RenderData.ViewMatrix = viewMatrix;
		m_RenderData.ProjectionMatrix = projectionMatrix;
	}

	void Renderer::End()
	{
		if (!HasBegun())
		{
			MN_WARN("Renderer::Begin must be called before Renderer::End.");
			return;
		}

		// Let inheriting classes sort objects
		Sort();

		// Render objects
		for (int i = 0; i < m_RenderObjects.size(); i++)
			Render(m_RenderObjects[i]);

		// Flush data, we want a clean slate
		m_RenderData.Context = nullptr;
		m_RenderData.ViewMatrix = glm::mat4(1.f);
		m_RenderData.ProjectionMatrix = glm::mat4(1.f);
		m_RenderObjects.clear();
	}

	void Renderer::SetRenderTarget(FrameBuffer* frameBuffer)
	{
		if (HasBegun())
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
		if (!HasBegun())
		{
			MN_WARN("Call Renderer::Begin before clearing.");
			return;
		}

		m_RenderData.Context->Clear(flags);
	}

	void Renderer::Submit(const Transform& transform, Mesh* mesh, Material* material)
	{
		if (!HasBegun())
		{
			MN_WARN("Call Renderer::Begin before submitting.");
			return;
		}

		m_RenderObjects.push_back({ transform, mesh, material });
	}

	void Renderer::Render(const FrameBuffer* frameBuffer, Shader* shader)
	{
		if (!HasBegun())
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

	void Renderer::Render(const RenderObject& object)
	{
		auto& material = object.Material;
		material->GetShader()->Set("u_Projection", m_RenderData.ProjectionMatrix);
		material->GetShader()->Set("u_View", m_RenderData.ViewMatrix);
		material->GetShader()->Set("u_Model", object.Transform.GetMatrix());

		material->Bind();
		m_RenderData.Context->Render(object.Mesh->GetVertexArray());
		material->Unbind();
	}
}