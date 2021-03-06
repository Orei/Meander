#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace Meander
{
	enum class ShaderType
	{
		None = -1,
		Vertex,
		Fragment
	};

	class Shader
	{
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void Set(const char* name, const int value) = 0;
		virtual void Set(const char* name, const float value) = 0;
		virtual void Set(const char* name, const glm::vec2& value) = 0;
		virtual void Set(const char* name, const glm::vec3& value) = 0;
		virtual void Set(const char* name, const glm::vec4& value) = 0;
		virtual void Set(const char* name, const glm::mat4& value) = 0;

		static Shader* Create(const char* path);
	};
}