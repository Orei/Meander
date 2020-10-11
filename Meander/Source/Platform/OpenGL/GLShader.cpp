#include "pch.h"
#include "GLShader.h"
#include "Meander/Utility/File.h"
#include "Meander/Utility/Path.h"
#include <sstream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

namespace Meander
{
	GLShader::GLShader(const char* path)
	{
		std::string vertexSource;
		std::string fragmentSource;
		ParseShaders(path, vertexSource, fragmentSource);
		CreateProgram(vertexSource.c_str(), fragmentSource.c_str());
	}

	GLShader::~GLShader()
	{
		glDeleteProgram(m_Handle);
	}

	void GLShader::Bind() const
	{
		glUseProgram(m_Handle);
	}

	void GLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void GLShader::ParseShaders(const char* path, std::string& vertexSource, std::string& fragmentSource)
	{
		static const char* VERTEX_TOKEN = "Vertex";
		static const char* FRAGMENT_TOKEN = "Fragment";
		static const char* DEPTH_ENTER_TOKEN = "{";
		static const char* DEPTH_EXIT_TOKEN = "}";
		static const char* INCLUDE_TOKEN = "#include";

		std::ifstream stream(path);
		if (!stream.good())
		{
			MN_ERROR("Unable to read file '{0}'.", path);
			return;
		}

		int depth = 0;
		ShaderType type = ShaderType::None;

		std::string line;
		std::stringstream ss[2];

		while (getline(stream, line))
		{
			if (line.find(VERTEX_TOKEN) != std::string::npos && depth == 0) { type = ShaderType::Vertex; continue; }
			if (line.find(FRAGMENT_TOKEN) != std::string::npos && depth == 0) { type = ShaderType::Fragment; continue; }
			if (line.find(DEPTH_ENTER_TOKEN) != std::string::npos) { if (++depth == 1) continue; }
			if (line.find(DEPTH_EXIT_TOKEN) != std::string::npos) { if (--depth == 0) continue; }

			if (line.find(INCLUDE_TOKEN) != std::string::npos)
			{
				size_t begin = line.find("\"") + 1;
				size_t end = line.find("\"", begin);

				std::string directory = Path::GetDirectory(path);
				std::string file = line.substr(begin, end - begin);
				std::string path = Path::Combine(directory, file);

				std::string content;
				if (!File::Read(path.c_str(), content))
					continue;

				ss[(int)type] << content << std::endl;
				continue;
			}

			if (type == ShaderType::None) continue;
			ss[(int)type] << line << std::endl;
		}

		vertexSource = ss[(int)ShaderType::Vertex].str();
		fragmentSource = ss[(int)ShaderType::Fragment].str();
	}

	void GLShader::CreateProgram(const char* vertexSource, const char* fragmentSource)
	{
		// Create and compile shaders
		GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexSource);
		GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentSource);

		// Create program
		m_Handle = glCreateProgram();

		// Attach and link
		glAttachShader(m_Handle, vertexShader);
		glAttachShader(m_Handle, fragmentShader);
		glLinkProgram(m_Handle);

		// Ensure that our program works
		ValidateProgram();

		// Clean up
		glDetachShader(m_Handle, vertexShader);
		glDetachShader(m_Handle, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	uint32_t GLShader::CreateShader(uint32_t glShaderType, const char* source)
	{
		GLuint shader = glCreateShader(glShaderType);
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);

		ValidateShader(shader);

		return shader;
	}

	bool GLShader::ValidateShader(uint32_t handle)
	{
		GLint status;
		glGetProgramiv(handle, GL_COMPILE_STATUS, &status);

		if (!status)
		{
			char logBuffer[1024];
			glGetProgramInfoLog(m_Handle, 1024, nullptr, logBuffer);

			MN_ERROR("Unable to compile shader: {0}", logBuffer);
			return false;
		}

		return true;
	}

	bool GLShader::ValidateProgram()
	{
		GLint status;
		glGetProgramiv(m_Handle, GL_LINK_STATUS, &status);

		if (!status)
		{
			char logBuffer[1024];
			glGetProgramInfoLog(m_Handle, 1024, nullptr, logBuffer);

			MN_ERROR("Unable to link shader program: {0}", logBuffer);
			return false;
		}

		return true;
	}

	/* Uniforms */
	void GLShader::Set(const char* name, const int value)
	{
		glUseProgram(m_Handle);
		uint32_t location = GetUniformLocation(name);
		glUniform1i(location, value);
		glUseProgram(0);
	}

	void GLShader::Set(const char* name, const float value)
	{
		glUseProgram(m_Handle);
		uint32_t location = GetUniformLocation(name);
		glUniform1f(location, value);
		glUseProgram(0);
	}

	void GLShader::Set(const char* name, const glm::vec2& value)
	{
		glUseProgram(m_Handle);
		uint32_t location = GetUniformLocation(name);
		glUniform2fv(location, 1, glm::value_ptr(value));
		glUseProgram(0);
	}

	void GLShader::Set(const char* name, const glm::vec3& value)
	{
		glUseProgram(m_Handle);
		uint32_t location = GetUniformLocation(name);
		glUniform3fv(location, 1, glm::value_ptr(value));
		glUseProgram(0);
	}

	void GLShader::Set(const char* name, const glm::vec4& value)
	{
		glUseProgram(m_Handle);
		uint32_t location = GetUniformLocation(name);
		glUniform4fv(location, 1, glm::value_ptr(value));
		glUseProgram(0);
	}

	void GLShader::Set(const char* name, const glm::mat4& value)
	{
		glUseProgram(m_Handle);
		uint32_t location = GetUniformLocation(name);
		glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
		glUseProgram(0);
	}

	uint32_t GLShader::GetUniformLocation(const char* name)
	{
		uint32_t location = (uint32_t)glGetUniformLocation(m_Handle, name);
		return location;
	}
}