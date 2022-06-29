#include <Junia.hpp>

class ExampleLayer : public Junia::Layer
{
public:
	ExampleLayer() : Junia::Layer("Example Layer"), camera(-1.0f, 1.0f, -1.0f, 1.0f), cameraPosition(0.0f)
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

		std::shared_ptr<Junia::VertexBuffer> vertexBuffer = std::shared_ptr<Junia::VertexBuffer>(
			Junia::VertexBuffer::Create(vertices, sizeof(vertices))
		);

		Junia::BufferLayout layout = {
			{ Junia::ShaderDataType::Float3, "inPosition" },
			{ Junia::ShaderDataType::Float4, "inColor" }
		};
		vertexBuffer->SetLayout(layout);
		vertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Junia::IndexBuffer> indexBuffer = std::shared_ptr<Junia::IndexBuffer>(
			Junia::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t))
		);
		vertexArray->SetIndexBuffer(indexBuffer);

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f, 0.75f, 0.0f,
			-0.75f, 0.75f, 0.0f
		};

		squareVertexArray.reset(Junia::VertexArray::Create());
		std::shared_ptr<Junia::VertexBuffer> squareVertexBuffer = std::shared_ptr<Junia::VertexBuffer>(
			Junia::VertexBuffer::Create(squareVertices, sizeof(squareVertices))
		);

		squareVertexBuffer->SetLayout({
			{ Junia::ShaderDataType::Float3, "inPosition" }
			});
		squareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Junia::IndexBuffer> squareIndexBuffer = std::shared_ptr<Junia::IndexBuffer>(
			Junia::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t))
		);
		squareVertexArray->SetIndexBuffer(squareIndexBuffer);

		std::string vertexSrc = R"(
			#version 450

			layout(location = 0) in vec3 inPosition;
			layout(location = 1) in vec4 inColor;

			uniform mat4 u_ViewProjection;

			out vec3 vPosition;
			out vec4 vColor;

			void main()
			{
				vPosition = inPosition;
				vColor = inColor;
				gl_Position = u_ViewProjection * vec4(inPosition, 1.0);
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

			out vec3 vPosition;

			void main()
			{
				vPosition = inPosition;
				gl_Position = u_ViewProjection * vec4(inPosition, 1.0);
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

		Junia::Renderer::Submit(shader2, squareVertexArray);
		Junia::Renderer::Submit(shader, vertexArray);

		Junia::Renderer::EndScene();
	}

private:
	std::shared_ptr<Junia::Shader> shader;
	std::shared_ptr<Junia::VertexArray> vertexArray;

	std::shared_ptr<Junia::Shader> shader2;
	std::shared_ptr<Junia::VertexArray> squareVertexArray;

	Junia::OrthographicCamera camera;
	glm::vec3 cameraPosition;
	float cameraMoveSpeed = 5.0f;
	float cameraRotation = 0.0f;
	float cameraRotationSpeed = 180.0f;
};

class Testapp : public Junia::Application
{
public:
	Testapp() { PushLayerFront(new ExampleLayer()); }
	~Testapp() override = default;
};

Junia::Application* Junia::CreateApplication() { return new Testapp(); }
