#pragma once
#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Meander
{
	class Transform
	{
	public:
		glm::vec3 Position = glm::vec3(0.f);
		glm::quat Rotation = glm::identity<glm::quat>();
		glm::vec3 Scale = glm::vec3(1.f);

		Transform() {}
		Transform(const glm::vec3& Position) 
			: Position(Position) {}
		Transform(const glm::vec3& Position, const glm::quat& Rotation) 
			: Position(Position), Rotation(Rotation) {}
		Transform(const glm::vec3& Position, const glm::quat& Rotation, const glm::vec3& Scale) 
			: Position(Position), Rotation(Rotation), Scale(Scale) {}

		glm::mat4 GetMatrix() const;
		Transform operator*(const Transform& other) const;
	};
}