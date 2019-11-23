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

		const glm::vec3& GetPosition() const { return m_Transform.Position; }
		void SetPosition(const glm::vec3& position) { m_Transform.Position = position; Recalculate(); }

		const glm::quat& GetRotation() const { return m_Transform.Rotation; }
		void SetRotation(const glm::quat& rotation) { m_Transform.Rotation = rotation; Recalculate(); }

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

	private:
		Transform m_Transform;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		glm::vec3 m_Forward;
		glm::vec3 m_Right;
		glm::vec3 m_Up;

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
		PerspectiveCamera(float fov, float ratio, float zNear = 0.1f, float zFar = 150.f);
	};
}