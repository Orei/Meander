#include "pch.h"
#include "Camera.h"

namespace Meander
{
	/* Generic */
	void Camera::RecalculateView()
	{
		m_ViewMatrix = glm::lookAt(GetTransform().GetPosition(), 
			GetTransform().GetPosition() + GetTransform().GetForward(), 
			GetTransform().GetUp());
	}

	/* Orthographic */
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float zNear, float zFar)
		: m_Left(left), m_Right(right), m_Bottom(bottom), m_Top(top), m_ZNear(zNear), m_ZFar(zFar)
	{
	}

	void OrthographicCamera::RecalculateProjection()
	{
		m_ProjectionMatrix = glm::ortho(m_Left, m_Right, m_Bottom, m_Top, m_ZNear, m_ZFar);
	}

	/* Perspective */
	PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float zNear, float zFar)
		: m_FOV(fov), m_AspectRatio(aspectRatio), m_ZNear(zNear), m_ZFar(zFar)
	{
	}

	void PerspectiveCamera::RecalculateProjection()
	{
		m_ProjectionMatrix = glm::perspective(m_FOV, m_AspectRatio, m_ZNear, m_ZFar);
	}
}