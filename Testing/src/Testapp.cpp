#include <Junia.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Junia/Platform/OpenGL/OpenGLShader.hpp>

class ExampleLayer : public Junia::Layer
{
public:
	ExampleLayer() : Junia::Layer("Example Layer"), camera(-2.0f, 2.0f, -1.5f, 1.5f), cameraPosition(0.0f)
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

		Junia::Ref<Junia::VertexBuffer> vertexBuffer = Junia::Ref<Junia::VertexBuffer>(
			Junia::VertexBuffer::Create(vertices, sizeof(vertices))
		);

		Junia::BufferLayout layout = {
			{ Junia::ShaderDataType::Float3, "inPosition" },
			{ Junia::ShaderDataType::Float4, "inColor"    }
		};
		vertexBuffer->SetLayout(layout);
		vertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Junia::Ref<Junia::IndexBuffer> indexBuffer = Junia::Ref<Junia::IndexBuffer>(
			Junia::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t))
		);
		vertexArray->SetIndexBuffer(indexBuffer);

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		squareVertexArray.reset(Junia::VertexArray::Create());
		Junia::Ref<Junia::VertexBuffer> squareVertexBuffer = Junia::Ref<Junia::VertexBuffer>(
			Junia::VertexBuffer::Create(squareVertices, sizeof(squareVertices))
		);

		squareVertexBuffer->SetLayout({
			{ Junia::ShaderDataType::Float3, "inPosition" }
			});
		squareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Junia::Ref<Junia::IndexBuffer> squareIndexBuffer = Junia::Ref<Junia::IndexBuffer>(
			Junia::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t))
		);
		squareVertexArray->SetIndexBuffer(squareIndexBuffer);

		std::string vertexSrc = R"(
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

		shader.reset(Junia::Shader::Create(vertexSrc, fragmentSrc));

		std::string vertexSrc2 = R"(
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

		std::string fragmentSrc2 = R"(
			#version 450

			layout(location = 0) out vec4 outColor;

			in vec3 vPosition;

			uniform vec3 u_Color;

			void main()
			{
				outColor = vec4(u_Color, 1.0f);
			}
		)";

		shader2.reset(Junia::Shader::Create(vertexSrc2, fragmentSrc2));
	}

	void OnUpdate(Junia::Timestep deltaTime) override
	{
		if (Junia::Input::IsKeyDown(JE_KEY_LEFT))
			cameraPosition.x -= cameraMoveSpeed * deltaTime;
		else if (Junia::Input::IsKeyDown(JE_KEY_RIGHT))
			cameraPosition.x += cameraMoveSpeed * deltaTime;
		if (Junia::Input::IsKeyDown(JE_KEY_UP))
			cameraPosition.y += cameraMoveSpeed * deltaTime;
		else if (Junia::Input::IsKeyDown(JE_KEY_DOWN))
			cameraPosition.y -= cameraMoveSpeed * deltaTime;

		if (Junia::Input::IsKeyDown(JE_KEY_A))
			cameraRotation += cameraRotationSpeed * deltaTime;
		if (Junia::Input::IsKeyDown(JE_KEY_D))
			cameraRotation -= cameraRotationSpeed * deltaTime;
	}

	void OnUpdate() override
	{
		Junia::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Junia::RenderCommand::Clear();

		camera.SetPosition(cameraPosition);
		camera.SetRotation(cameraRotation);

		Junia::Renderer::BeginScene(camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Junia::OpenGLShader>(shader2)->Bind();
		std::dynamic_pointer_cast<Junia::OpenGLShader>(shader2)->UploadUniformFloat3("u_Color", squareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * .11f, y * .11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Junia::Renderer::Submit(shader2, squareVertexArray, transform);
			}
		}
		Junia::Renderer::Submit(shader, vertexArray);

		Junia::Renderer::EndScene();
	}

private:
	Junia::Ref<Junia::Shader> shader;
	Junia::Ref<Junia::VertexArray> vertexArray;

	Junia::Ref<Junia::Shader> shader2;
	Junia::Ref<Junia::VertexArray> squareVertexArray;

	Junia::OrthographicCamera camera;
	glm::vec3 cameraPosition;
	float cameraMoveSpeed = 5.0f;
	float cameraRotation = 0.0f;
	float cameraRotationSpeed = 180.0f;

	glm::vec3 squareColor = { .2f, .3f, .8f };
};

class Testapp : public Junia::Application
{
public:
	Testapp() { PushLayerBack(new ExampleLayer()); }
	~Testapp() override = default;
};

Junia::Application* Junia::CreateApplication() { return new Testapp(); }
