#include "pch.h"
#include "Camera.h"

namespace Meander
{
	/* Generic */
	void Camera::Recalculate()
	{
		m_ViewMatrix = glm::lookAt(GetTransform().GetPosition(), GetTransform().GetPosition() + GetTransform().GetForward(), GetTransform().GetUp());
	}

	/* Orthographic */
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float zNear, float zFar)
		: Camera(glm::ortho(left, right, bottom, top, zNear, zFar))
	{
	}

	/* Perspective */
	PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float zNear, float zFar)
		: Camera(glm::perspective(fov, aspectRatio, zNear, zFar))
	{
	}
}