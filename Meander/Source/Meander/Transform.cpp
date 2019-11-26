#include "pch.h"
#include "Transform.h"
#include <glm/gtx/matrix_decompose.hpp>

namespace Meander
{
	void Transform::SetEuler(const glm::vec3& euler)
	{
		float pitch = euler.x * 0.5f;
		float sinPitch = sin(pitch);
		float cosPitch = cos(pitch);

		float yaw = euler.y * 0.5f;
		float sinYaw = sin(yaw);
		float cosYaw = cos(yaw);

		float roll = euler.z * 0.5f;
		float sinRoll = sin(roll);
		float cosRoll = cos(roll);

		m_Rotation.x = ((cosYaw * sinPitch) * cosRoll) + ((sinYaw * cosPitch) * sinRoll);
		m_Rotation.y = ((sinYaw * cosPitch) * cosRoll) - ((cosYaw * sinPitch) * sinRoll);
		m_Rotation.z = ((cosYaw * cosPitch) * sinRoll) - ((sinYaw * sinPitch) * cosRoll);
		m_Rotation.w = ((cosYaw * cosPitch) * cosRoll) + ((sinYaw * sinPitch) * sinRoll);
	}
	
	glm::vec3 Transform::GetEuler() const
	{
		float roll = atan2(2 * (m_Rotation.x * m_Rotation.y + m_Rotation.z * m_Rotation.w),
			(1 - 2 * (m_Rotation.y * m_Rotation.y + m_Rotation.z * m_Rotation.z)));
		float pitch = asin(2 * (m_Rotation.x * m_Rotation.z - m_Rotation.w * m_Rotation.y));
		float yaw = atan2(2 * (m_Rotation.x * m_Rotation.w + m_Rotation.y * m_Rotation.z),
			(1 - 2 * (m_Rotation.z * m_Rotation.z + m_Rotation.w * m_Rotation.w)));

		return glm::vec3(pitch, yaw, roll);
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