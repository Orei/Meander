#pragma once
#include "Meander/Transform.h"
#include <glm/mat4x4.hpp>

namespace Meander
{
	class Mesh;
	class Material;
	class Context;
	class FrameBuffer;
	class Shader;
	class CubeMap;
	enum class ClearFlags;

	class Renderer
	{
	public:
		/* Begins a new render-scene. */
		void Begin(const glm::mat4& viewMatrix = glm::mat4(1.f), const glm::mat4& projectionMatrix = glm::mat4(1.f));
		
		/* Ends the active render-scene; renders submitted objects. */
		void End();

		/* Sets the active framebuffer which will be rendered to. Reset using a nullptr. */
		void SetRenderTarget(FrameBuffer* frameBuffer);

		/* Clears the active framebuffer. */
		void Clear(const ClearFlags& flags);

		/* Submits a mesh to the render-queue. */
		void Submit(const Transform& transform, Mesh* mesh, Material* material);

		/* Renders a framebuffer to screen. */
		void Render(const FrameBuffer* frameBuffer, Shader* shader);

		/* Whether the render-scene has begun. */
		bool HasBegun() { return m_RenderData.Context != nullptr; }

	protected:
		struct RenderData
		{
			Context* Context = nullptr;
			glm::mat4 ViewMatrix = glm::mat4(1.f);
			glm::mat4 ProjectionMatrix = glm::mat4(1.f);
			FrameBuffer* FrameBuffer = nullptr;
		};

		struct RenderObject
		{
			RenderObject(const Transform& transform, Mesh* mesh, Material* material)
				: Transform(transform), Mesh(mesh), Material(material)
			{
			}

			Transform Transform = {};
			Mesh* Mesh = nullptr;
			Material* Material = nullptr;
		};

		/* Sorts the objects prior to rendering. */
		virtual void Sort() = 0;

		/* Renders the render-object. */
		void Render(const RenderObject& object);

		/* Contains render-scene data. */
		RenderData m_RenderData;
		std::vector<RenderObject> m_RenderObjects;
	};
}