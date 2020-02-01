#pragma once
#include "Meander/Graphics/Shader.h"

namespace Meander
{
	class GLShader : public Shader
	{
	public:
		GLShader(const char* path);
		virtual ~GLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void Set(const char* name, const int value) const override;
		virtual void Set(const char* name, const float value) const override;
		virtual void Set(const char* name, const glm::vec2& value) const override;
		virtual void Set(const char* name, const glm::vec3& value) const override;
		virtual void Set(const char* name, const glm::vec4& value) const override;
		virtual void Set(const char* name, const glm::mat4& value) const override;

	private:
		unsigned int m_Handle = 0;

		void ParseShaders(const char* path, std::string& vertexSource, std::string& fragmentSource);
		void CreateProgram(const char* vertexSource, const char* fragmentSource);
		unsigned int CreateShader(unsigned int glShaderType, const char* source);
		bool ValidateShader(unsigned int handle);
		bool ValidateProgram();
	};
}