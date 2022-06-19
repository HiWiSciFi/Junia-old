#include "Application.hpp"

#include <Junia/Log.hpp>
#include <Junia/Events/EventSystem.hpp>
#include <functional>
#include <glad/glad.h>
#include <Junia/Renderer/Renderer.hpp>

namespace Junia
{
	Application* Application::app;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Junia::ShaderDataType::Float:
		case Junia::ShaderDataType::Float2:
		case Junia::ShaderDataType::Float3:
		case Junia::ShaderDataType::Float4:
		case Junia::ShaderDataType::Mat3:
		case Junia::ShaderDataType::Mat4:   return GL_FLOAT;
		case Junia::ShaderDataType::Int:
		case Junia::ShaderDataType::Int2:
		case Junia::ShaderDataType::Int3:
		case Junia::ShaderDataType::Int4:     return GL_INT;
		case Junia::ShaderDataType::Bool:    return GL_BOOL;
		default:
			JELOG_BASE_ERROR("Unknown ShaderDataType!");
			return GL_NONE;
		}
	}

	Application::Application()
	{
		app = this;
		window = std::unique_ptr<Window>(Window::Create());
		WindowCloseEvent::Subscribe(JE_EVENTTYPE_BIND_MEMBER_FUNC(WindowCloseEvent, OnWindowClosed));

		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
		};

		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "inPosition" },
			{ ShaderDataType::Float4, "inColor"    }
		};
		vertexBuffer->SetLayout(layout);

		for (int i = 0; i < vertexBuffer->GetLayout().GetElements().size(); i++)
		{
			const auto& element = vertexBuffer->GetLayout().GetElements()[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(
				i,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				*((const void**)&element.offset)
			);
		}

		uint32_t indices[3] = { 0, 1, 2 };
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		std::string vertexSrc = R"(
			#version 450

			layout(location = 0) in vec3 inPosition;
			layout(location = 1) in vec4 inColor;

			out vec3 vPosition;
			out vec4 vColor;

			void main()
			{
				vPosition = inPosition;
				vColor = inColor;
				gl_Position = vec4(inPosition, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 450

			layout(location = 0) out vec4 outColor;

			in vec3 vPosition;
			in vec4 vColor;

			void main()
			{
				outColor = vec4(vPosition * 0.5 + 0.5, 1.0);
				outColor = vColor;
			}
		)";

		shader.reset(Shader::Create(vertexSrc, fragmentSrc));
	}

	Application::~Application() = default;

	Layer* Application::PushLayerFront(Layer* layer) { return layerSystem.PushLayerFront(layer); }
	Layer* Application::PushLayerBack(Layer* layer) { return layerSystem.PushLayerBack(layer); }
	Layer* Application::PopLayerFront() { return layerSystem.PopLayerFront(); }
	Layer* Application::PopLayerBack() { return layerSystem.PopLayerBack(); }

	void Application::Run() const
	{
		while (running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shader->Bind();
			glBindVertexArray(vertexArray);
			glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			EventSystem::DispatchQueue();
			layerSystem.IterateForward([](Layer* layer) { layer->OnUpdate(); });
			window->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(const WindowCloseEvent* e)
	{
		layerSystem.~LayerSystem();
		running = false;
		return true;
	}
}
