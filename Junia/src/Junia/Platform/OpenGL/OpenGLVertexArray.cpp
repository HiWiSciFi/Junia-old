#ifdef JE_GAPI_SUPPORTED_OPENGL

#include "OpenGLVertexArray.hpp"
#include <glad/glad.h>

namespace Junia
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Junia::ShaderDataType::Float:
		case Junia::ShaderDataType::Float2:
		case Junia::ShaderDataType::Float3:
		case Junia::ShaderDataType::Float4:
		case Junia::ShaderDataType::Mat3:
		case Junia::ShaderDataType::Mat4: return GL_FLOAT;
		case Junia::ShaderDataType::Int:
		case Junia::ShaderDataType::Int2:
		case Junia::ShaderDataType::Int3:
		case Junia::ShaderDataType::Int4: return GL_INT;
		case Junia::ShaderDataType::Bool: return GL_BOOL;
		default:
			JELOG_BASE_ERROR("Unknown ShaderDataType!");
			return GL_NONE;
		}
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &rendererId);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &rendererId);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(rendererId);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(Ref<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(rendererId);
		vertexBuffer->Bind();
		for (size_t i = 0; i < vertexBuffer->GetLayout().GetElements().size(); i++)
		{
			const Junia::BufferElement& element = vertexBuffer->GetLayout().GetElements()[i];
			glEnableVertexAttribArray(static_cast<GLuint>(i));
			// This debugging remnant will stay here forever as a reminder of the lost week
			/*JELOG_BASE_ERROR(
				"Pointers: %u : %p : %p",
				element.offset,
				*((const void**)&element.offset),
				reinterpret_cast<const void*>(static_cast<unsigned long long>(element.offset))
			);*/
			glVertexAttribPointer(
				static_cast<GLuint>(i),
				static_cast<GLint>(element.GetComponentCount()),
				ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				static_cast<GLsizei>(vertexBuffer->GetLayout().GetStride()),
				// wtf?????
				// fixes no rendered output...
				// idk why
				// please send help
				// why does this:
				//*((const void**)&element.offset)
				// not work but this does:
				reinterpret_cast<const void*>(static_cast<unsigned long long>(element.offset))
				// i am so confused...
			);
		}
		vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& nindexBuffer)
	{
		glBindVertexArray(rendererId);
		nindexBuffer->Bind();

		indexBuffer = nindexBuffer;
	}
}

#endif
