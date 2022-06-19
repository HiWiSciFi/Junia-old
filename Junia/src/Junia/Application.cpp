#include "Application.hpp"

#include <Junia/Log.hpp>
#include <Junia/Events/EventSystem.hpp>
#include <functional>
#include <glad/glad.h>
#include <Junia/Renderer/Renderer.hpp>

namespace Junia
{
	Application* Application::app;

	Application::Application()
	{
		app = this;
		window = std::unique_ptr<Window>(Window::Create());
		WindowCloseEvent::Subscribe(JE_EVENTTYPE_BIND_MEMBER_FUNC(WindowCloseEvent, OnWindowClosed));

		vertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "inPosition" },
			{ ShaderDataType::Float4, "inColor" }
		};
		vertexBuffer->SetLayout(layout);
		vertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		vertexArray->SetIndexBuffer(indexBuffer);

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		squareVertexArray.reset(VertexArray::Create());
		std::shared_ptr<VertexBuffer> squareVertexBuffer = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "inPosition" }
		});
		squareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIndexBuffer = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		squareVertexArray->SetIndexBuffer(squareIndexBuffer);

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

		std::string vertexSrc2 = R"(
			#version 450

			layout(location = 0) in vec3 inPosition;

			out vec3 vPosition;

			void main()
			{
				vPosition = inPosition;
				gl_Position = vec4(inPosition, 1.0);
			}
		)";

		std::string fragmentSrc2 = R"(
			#version 450

			layout(location = 0) out vec4 outColor;

			in vec3 vPosition;

			void main()
			{
				outColor = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		shader2.reset(Shader::Create(vertexSrc2, fragmentSrc2));
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

			shader2->Bind();
			squareVertexArray->Bind();
			glDrawElements(GL_TRIANGLES, squareVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			shader->Bind();
			vertexArray->Bind();
			glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

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
