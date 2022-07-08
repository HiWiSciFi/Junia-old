#ifdef JE_GAPI_SUPPORTED_OPENGL

#include "OpenGLRendererAPI.hpp"

#include <glad/glad.h>
#include <Junia/Core/Log.hpp>

namespace Junia
{
	void GLAPIENTRY OpenGLMessageCallback(GLenum, GLenum, GLuint, GLenum severity, GLsizei, const GLchar* message, const void*)
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
		glViewport(static_cast<GLint>(x), static_cast<GLint>(y), static_cast<GLint>(width), static_cast<GLint>(height));
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
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vertexArray->GetIndexBuffer()->GetCount()), GL_UNSIGNED_INT, nullptr);
	}
}

#endif
