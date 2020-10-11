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
		virtual void Set(const char* name, const int value) override;
		virtual void Set(const char* name, const float value) override;
		virtual void Set(const char* name, const glm::vec2& value) override;
		virtual void Set(const char* name, const glm::vec3& value) override;
		virtual void Set(const char* name, const glm::vec4& value) override;
		virtual void Set(const char* name, const glm::mat4& value) override;
	
	private:
		uint32_t m_Handle = 0;

		void ParseShaders(const char* path, std::string& vertexSource, std::string& fragmentSource);
		void CreateProgram(const char* vertexSource, const char* fragmentSource);
		uint32_t CreateShader(uint32_t glShaderType, const char* source);
		bool ValidateShader(uint32_t handle);
		bool ValidateProgram();
		uint32_t GetUniformLocation(const char* name);
	};
}