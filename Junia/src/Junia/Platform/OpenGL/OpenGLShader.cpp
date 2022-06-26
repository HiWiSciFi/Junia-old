#include "OpenGLShader.hpp"

#include <Junia/Log.hpp>
#include <glad/glad.h>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

namespace Junia
{
	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = static_cast<const GLchar*>(vertexSrc.c_str());
		glShaderSource(vertexShader, 1, &source, 0);

		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);
			JELOG_BASE_ERROR(infoLog.data());
			return;
		}


		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = static_cast<const GLchar*>(fragmentSrc.c_str());
		glShaderSource(fragmentShader, 1, &source, 0);

		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			JELOG_BASE_ERROR(infoLog.data());
			return;
		}

		rendererId = glCreateProgram();

		glAttachShader(rendererId, vertexShader);
		glAttachShader(rendererId, fragmentShader);

		glLinkProgram(rendererId);

		GLint isLinked = 0;
		glGetProgramiv(rendererId, GL_LINK_STATUS, static_cast<int*>(&isLinked));
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(rendererId, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(rendererId, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(rendererId);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			JELOG_BASE_ERROR(infoLog.data());
			return;
		}

		glDetachShader(rendererId, vertexShader);
		glDetachShader(rendererId, fragmentShader);
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
