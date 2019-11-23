#include "pch.h"
#include "Transform.h"
#include <glm/gtx/matrix_decompose.hpp>

namespace Meander
{
	glm::mat4 Transform::GetMatrix() const
	{
		glm::mat4 scale = glm::scale(glm::mat4(1.f), Scale);
		glm::mat4 rotation = glm::mat4_cast(Rotation);
		glm::mat4 position = glm::translate(glm::mat4(1.f), Position);

		return position * rotation * scale;
	}

	Transform Transform::operator*(const Transform& other) const
	{
		glm::mat4 matrix = GetMatrix() * other.GetMatrix();

		Transform transform;
		glm::vec3 skew;
		glm::vec4 perspective;

		glm::decompose(matrix, transform.Scale, transform.Rotation, transform.Position, skew, perspective);
		return transform;
	}
}