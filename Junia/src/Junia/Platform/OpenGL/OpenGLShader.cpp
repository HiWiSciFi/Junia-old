#include "OpenGLShader.hpp"

#include <Junia/Log.hpp>
#include <Junia/Platform/Platform.hpp>
#include <glad/glad.h>
#include <vector>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

namespace Junia
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")                      return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;
		JELOG_BASE_ERROR("Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string source = Platform::ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);

		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) : rendererId(0), name(name)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(rendererId);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(rendererId);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\n", pos);
			if (eol == std::string::npos) JELOG_BASE_ERROR("Shader syntax error!");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			if (type != "vertex" && type != "fragment" && type != "pixel") JELOG_BASE_ERROR("Invalid Shader type!");

			size_t nextLinePos = source.find_first_not_of("\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] =
				source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string> shaderSources)
	{
		GLuint program = glCreateProgram();
		std::vector<GLenum> glShaderIDs;
		glShaderIDs.reserve(shaderSources.size());
		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceC = static_cast<const GLchar*>(source.c_str());
			glShaderSource(shader, 1, &sourceC, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);
				JELOG_BASE_ERROR("Shader could not be compiled! Error: " JELOG_CSTR, infoLog.data());
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs.push_back(shader);
		}

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, static_cast<int*>(&isLinked));
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			for (auto id : glShaderIDs) glDeleteShader(id);
			JELOG_BASE_ERROR(infoLog.data());
			return;
		}

		for (auto id : glShaderIDs) glDetachShader(program, id);

		rendererId = program;
	}

	void OpenGLShader::UploadUniformInt(const std::string name, int value)
	{
		GLint location = glGetUniformLocation(rendererId, name.c_str());
		if (location == -1)
		{
			JELOG_BASE_ERROR("Invalid Uniform name! \"" JELOG_CSTR "\"", name.c_str());
			return;
		}
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string name, float value)
	{
		GLint location = glGetUniformLocation(rendererId, name.c_str());
		if (location == -1)
		{
			JELOG_BASE_ERROR("Invalid Uniform name! \"" JELOG_CSTR "\"", name.c_str());
			return;
		}
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string name, const glm::vec2& values)
	{
		GLint location = glGetUniformLocation(rendererId, name.c_str());
		if (location == -1)
		{
			JELOG_BASE_ERROR("Invalid Uniform name! \"" JELOG_CSTR "\"", name.c_str());
			return;
		}
		glUniform2f(location, values.x, values.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string name, const glm::vec3& values)
	{
		GLint location = glGetUniformLocation(rendererId, name.c_str());
		if (location == -1)
		{
			JELOG_BASE_ERROR("Invalid Uniform name! \"" JELOG_CSTR "\"", name.c_str());
			return;
		}
		glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string name, const glm::vec4& values)
	{
		GLint location = glGetUniformLocation(rendererId, name.c_str());
		if (location == -1)
		{
			JELOG_BASE_ERROR("Invalid Uniform name! \"" JELOG_CSTR "\"", name.c_str());
			return;
		}
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(rendererId, name.c_str());
		if (location == -1)
		{
			JELOG_BASE_ERROR("Invalid Uniform name! \"" JELOG_CSTR "\"", name.c_str());
			return;
		}
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(rendererId, name.c_str());
		if (location == -1)
		{
			JELOG_BASE_ERROR("Invalid Uniform name! \"" JELOG_CSTR "\"", name.c_str());
			return;
		}
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}
