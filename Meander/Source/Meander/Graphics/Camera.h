#pragma once
#include "Meander/Transform.h"

namespace Meander
{
	class Camera
	{
	public:
		Camera(const glm::mat4 projection)
			: m_ProjectionMatrix(projection)
		{
			Recalculate();
		}

		Transform& GetTransform() { return m_Transform; }
		const glm::mat4& GetViewMatrix() { Recalculate(); return m_ViewMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

	private:
		Transform m_Transform;
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.f);
		glm::mat4 m_ViewMatrix = glm::mat4(1.f);

		void Recalculate();
	};

	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top, float zNear = -1.f, float zFar = 1.f);
	};

	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fov, float aspectRatio, float zNear = 0.1f, float zFar = 150.f);
	};
}