#include <Junia.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <Junia/Platform/OpenGL/OpenGLShader.hpp>
#include <Junia/OrthographicCameraController.hpp>

class ExampleLayer : public Junia::Layer
{
public:
	ExampleLayer() : Junia::Layer("Example Layer"), cameraController(1280.0f / 720.0f, true)
	{
	}

	void OnEnable() override
	{
		vertexArray.reset(Junia::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f
		};

		auto vertexBuffer = Junia::Ref<Junia::VertexBuffer>(
			Junia::VertexBuffer::Create(vertices, sizeof(vertices))
		);

		const Junia::BufferLayout layout {
			{ Junia::ShaderDataType::Float3, "inPosition" },
			{ Junia::ShaderDataType::Float4, "inColor"    }
		};
		vertexBuffer->SetLayout(layout);
		vertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] { 0, 1, 2 };
		const auto indexBuffer = Junia::Ref<Junia::IndexBuffer>(
			Junia::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t))
		);
		vertexArray->SetIndexBuffer(indexBuffer);

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		squareVertexArray.reset(Junia::VertexArray::Create());
		auto squareVertexBuffer = Junia::Ref<Junia::VertexBuffer>(
			Junia::VertexBuffer::Create(squareVertices, sizeof(squareVertices))
		);

		squareVertexBuffer->SetLayout({
			{ Junia::ShaderDataType::Float3, "inPosition" },
			{ Junia::ShaderDataType::Float2, "texCoord" }
		});
		squareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		const auto squareIndexBuffer = Junia::Ref<Junia::IndexBuffer>(
			Junia::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t))
		);
		squareVertexArray->SetIndexBuffer(squareIndexBuffer);

		const std::string vertexSrc = R"(
			#version 450

			layout(location = 0) in vec3 inPosition;
			layout(location = 1) in vec4 inColor;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 vPosition;
			out vec4 vColor;

			void main()
			{
				vPosition = inPosition;
				vColor = inColor;
				gl_Position = u_ViewProjection * u_Transform * vec4(inPosition, 1.0);
			}
		)";

		const std::string fragmentSrc = R"(
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

		shader = Junia::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		const std::string vertexSrc2 = R"(
			#version 450

			layout(location = 0) in vec3 inPosition;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 vPosition;

			void main()
			{
				vPosition = inPosition;
				gl_Position = u_ViewProjection * u_Transform * vec4(inPosition, 1.0);
			}
		)";

		const std::string fragmentSrc2 = R"(
			#version 450

			layout(location = 0) out vec4 outColor;

			in vec3 vPosition;

			uniform vec3 u_Color;

			void main()
			{
				outColor = vec4(u_Color, 1.0f);
			}
		)";

		shader2 = Junia::Shader::Create("FlatColor", vertexSrc2, fragmentSrc2);

		const auto textureShader = shaderLibrary.Load("assets/shaders/Texture.glsl");

		texture = Junia::Texture2D::Create("assets/textures/Checkerboard.png");
		sdLogoTexture = Junia::Texture2D::Create("assets/textures/SDLogo.png");

		textureShader->Bind();
		//dynamic_cast<Junia::OpenGLShader>(*textureShader.get()).UploadUniformInt("u_Texture", 0);
		std::dynamic_pointer_cast<Junia::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

		Junia::WindowResizeEvent::Subscribe(JE_EVENTTYPE_BIND_MEMBER_FUNC(Junia::WindowResizeEvent, OnWindowResize));
	}

	bool OnWindowResize(const Junia::WindowResizeEvent& e)
	{
		/*float zoom = e.GetWidth() / 1280.0f;
		cameraController.SetZoomLevel(zoom);*/
		return false;
	}

	void OnUpdate(Junia::Timestep deltaTime) override
	{
		cameraController.OnUpdate(deltaTime);
	}

	void OnUpdate() override
	{
		Junia::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		//Junia::RenderCommand::SetClearColor({ 1.0f, 0.0f, 1.0f, 1.0f });
		Junia::RenderCommand::Clear();

		Junia::Renderer::BeginScene(cameraController.GetCamera());

		const glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		shader2->Bind();
		//dynamic_cast<Junia::OpenGLShader>(*shader2.get()).UploadUniformFloat3("u_Color", squareColor);
		std::dynamic_pointer_cast<Junia::OpenGLShader>(shader2)->UploadUniformFloat3("u_Color", squareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Junia::Renderer::Submit(shader2, squareVertexArray, transform);
			}
		}

		const auto textureShader = shaderLibrary.Get("Texture");

		texture->Bind();
		Junia::Renderer::Submit(textureShader, squareVertexArray,
			glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		sdLogoTexture->Bind();
		Junia::Renderer::Submit(textureShader, squareVertexArray,
			glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		//Junia::Renderer::Submit(shader, vertexArray);

		Junia::Renderer::EndScene();
	}

private:
	Junia::ShaderLibrary shaderLibrary;
	Junia::Ref<Junia::Shader> shader;
	Junia::Ref<Junia::VertexArray> vertexArray;

	Junia::Ref<Junia::Shader> shader2;
	Junia::Ref<Junia::VertexArray> squareVertexArray;

	Junia::Ref<Junia::Texture2D> texture, sdLogoTexture;

	Junia::OrthographicCameraController cameraController;

	glm::vec3 squareColor = { 0.2f, 0.3f, 0.8f };
};

class Testapp : public Junia::Application
{
public:
	Testapp() { PushLayerBack(new ExampleLayer()); }
	~Testapp() override = default;
};

Junia::Application* Junia::CreateApplication() { return new Testapp(); }
