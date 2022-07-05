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

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(rendererId);
		vertexBuffer->Bind();
		for (int i = 0; i < vertexBuffer->GetLayout().GetElements().size(); i++)
		{
			const auto& element = vertexBuffer->GetLayout().GetElements()[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(
				i,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				*((const void**)&element.offset)
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
