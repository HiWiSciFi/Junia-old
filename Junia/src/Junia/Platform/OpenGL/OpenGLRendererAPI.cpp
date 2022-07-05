#include "OpenGLRendererAPI.hpp"

#include <glad/glad.h>
#include <Junia/Core/Log.hpp>

namespace Junia
{
	void GLAPIENTRY OpenGLMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) JELOG_BASE_TRACE("OpenGL: " JELOG_CSTR, message);
		else if (severity == GL_DEBUG_SEVERITY_LOW) JELOG_BASE_INFO("OpenGL: " JELOG_CSTR, message);
		else if (severity == GL_DEBUG_SEVERITY_MEDIUM) JELOG_BASE_WARN("OpenGL: " JELOG_CSTR, message);
		else if (severity == GL_DEBUG_SEVERITY_HIGH) JELOG_BASE_ERROR("OpenGL: " JELOG_CSTR, message);
	}

	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(OpenGLMessageCallback, 0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
