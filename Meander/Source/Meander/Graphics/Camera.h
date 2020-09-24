#pragma once
#include "Meander/Math/Transform.h"

namespace Meander
{
	class Camera
	{
	public:
		Camera(){}
		Camera(const glm::mat4& projection)
			: m_ProjectionMatrix(projection)
		{
		}
		virtual ~Camera() { }

		Transform& GetTransform() { return m_Transform; }
		const glm::mat4& GetViewMatrix() { RecalculateView(); return m_ViewMatrix; }
		const glm::mat4& GetProjectionMatrix() { if (m_IsProjectionDirty) RecalculateProjection(); return m_ProjectionMatrix; }

	protected:
		Transform m_Transform = { };
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.f);
		glm::mat4 m_ViewMatrix = glm::mat4(1.f);
		bool m_IsProjectionDirty = true;
	
		virtual void RecalculateView();
		virtual void RecalculateProjection() = 0;
	};

	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top, float zNear = -1.f, float zFar = 1.f);

	protected:
		virtual void RecalculateProjection() override;

	private:
		float m_Left = 0.f;
		float m_Right = 1.f;
		float m_Bottom = 0.f;
		float m_Top = 1.f;
		float m_ZNear = -1.f;
		float m_ZFar = 1.f;
	};

	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fov, float aspectRatio, float zNear = 0.1f, float zFar = 150.f);

		void SetFOV(float fov) { m_FOV = fov; m_IsProjectionDirty = true; }
		void SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; m_IsProjectionDirty = true; }

	protected:
		virtual void RecalculateProjection() override;

	private:
		float m_FOV = 70.f;
		float m_AspectRatio = 1280.f / 720.f;
		float m_ZNear = 0.1f;
		float m_ZFar = 150.f;
	};
}