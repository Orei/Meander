#include "pch.h"
#include "Transform.h"
#include <glm/gtx/matrix_decompose.hpp>

namespace Meander
{
	void Transform::SetEuler(const glm::vec3& euler)
	{
		glm::vec3 h = euler * 0.5f;
		glm::vec3 s(sin(h.x), sin(h.y), sin(h.z));
		glm::vec3 c(cos(h.x), cos(h.y), cos(h.z));

		m_Rotation.x = s.x * c.y * c.z - c.x * s.y * s.z;
		m_Rotation.y = c.x * s.y * c.z + s.x * c.y * s.z;
		m_Rotation.z = c.x * c.y * s.z - s.x * s.y * c.z;
		m_Rotation.w = c.x * c.y * c.z + s.x * s.y * s.z;
	}

	glm::vec3 Transform::GetEuler() const
	{
		return glm::vec3(GetPitch(), GetYaw(), GetRoll());
	}

	float Transform::GetPitch() const
	{
		const float x = m_Rotation.x;
		const float y = m_Rotation.y;
		const float z = m_Rotation.z;
		const float w = m_Rotation.w;
		const float xx = x * x;
		const float yy = y * y;
		const float zz = z * z;
		const float ww = w * w;

		return atan2(2.f * (y * z + w * x), ww - xx - yy + zz);
	}

	float Transform::GetYaw() const
	{
		const float x = m_Rotation.x;
		const float y = m_Rotation.y;
		const float z = m_Rotation.z;
		const float w = m_Rotation.w;

		float value = -2.f * (x * z - w * y);
		value = fmin(fmax(-1.f, value), 1.f);

		return asin(value);
	}

	float Transform::GetRoll() const
	{
		const float x = m_Rotation.x;
		const float y = m_Rotation.y;
		const float z = m_Rotation.z;
		const float w = m_Rotation.w;
		const float xx = x * x;
		const float yy = y * y;
		const float zz = z * z;
		const float ww = w * w;

		return atan2(2.f * (x * y + w * z), ww + xx - yy - zz);
	}
	
	glm::mat4 Transform::GetMatrix() const
	{
		glm::mat4 scale = glm::scale(glm::mat4(1.f), m_Scale);
		glm::mat4 rotation = glm::mat4_cast(m_Rotation);
		glm::mat4 position = glm::translate(glm::mat4(1.f), m_Position);

		return position * rotation * scale;
	}

	Transform Transform::operator*(const Transform& other) const
	{
		glm::mat4 matrix = GetMatrix() * other.GetMatrix();

		Transform transform;
		glm::vec3 skew;
		glm::vec4 perspective;

		glm::decompose(matrix, transform.m_Scale, transform.m_Rotation,
			transform.m_Position, skew, perspective);

		return transform;
	}

	bool Transform::operator==(const Transform& other) const
	{
		return m_Position == other.m_Position 
			&& m_Rotation == other.m_Rotation 
			&& m_Scale == other.m_Scale;
	}
}