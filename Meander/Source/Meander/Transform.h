#pragma once
#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Meander
{
	enum class Space
	{
		Local,
		World
	};

	class Transform
	{
	public:
		Transform() {}
		Transform(const glm::vec3& Position) 
			: m_Position(Position) {}
		Transform(const glm::vec3& Position, const glm::quat& Rotation) 
			: m_Position(Position), m_Rotation(Rotation) {}
		Transform(const glm::vec3& Position, const glm::quat& Rotation, const glm::vec3& Scale) 
			: m_Position(Position), m_Rotation(Rotation), m_Scale(Scale) {}

		void SetPosition(const glm::vec3& position) { m_Position = position; }
		void SetRotation(const glm::quat& rotation) { m_Rotation = rotation; }
		void SetScale(const glm::vec3& scale) { m_Scale = scale; }
		void SetEuler(const glm::vec3& euler);

		void Translate(const glm::vec3& offset) { m_Position += offset; }
		void Rotate(float radians, const glm::vec3& axis) { Rotate(glm::angleAxis(radians, axis)); }
		void Rotate(const glm::quat& rotation) { m_Rotation = rotation * m_Rotation; }

		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::quat& GetRotation() const { return m_Rotation; }
		const glm::vec3& GetScale() const { return m_Scale; }
		glm::vec3 GetForward() const { return glm::conjugate(m_Rotation) * WORLD_FORWARD; }
		glm::vec3 GetRight() const { return glm::conjugate(m_Rotation) * WORLD_RIGHT; }
		glm::vec3 GetUp() const { return glm::conjugate(m_Rotation) * WORLD_UP; }
		glm::vec3 GetEuler() const;

		float GetPitch() const;
		float GetYaw() const;
		float GetRoll() const;
		glm::mat4 GetMatrix() const;
		
		Transform operator*(const Transform& other) const;
		bool operator==(const Transform& other) const;
		bool operator!=(const Transform& other) const { return !(*this == other); }

	private:
		glm::vec3 m_Position = glm::vec3(0.f);
		glm::quat m_Rotation = glm::identity<glm::quat>();
		glm::vec3 m_Scale = glm::vec3(1.f);

		glm::vec3 m_Forward = glm::vec3(0.f);
		glm::vec3 m_Right = glm::vec3(0.f);
		glm::vec3 m_Up = glm::vec3(0.f);
	};
}