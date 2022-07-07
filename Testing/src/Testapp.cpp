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

		shaderLibrary.Load("FlatColor", "assets/shaders/FlatColor.glsl");

		const auto textureShader = shaderLibrary.Load("Texture", "assets/shaders/Texture.glsl");
		texture = Junia::Texture2D::Create("assets/textures/Checkerboard.png");
		sdLogoTexture = Junia::Texture2D::Create("assets/textures/SDLogo.png");
		textureShader->Bind();
		std::dynamic_pointer_cast<Junia::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Junia::Timestep deltaTime) override
	{
		cameraController.OnUpdate(deltaTime);
	}

	void OnUpdate() override
	{
		Junia::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Junia::RenderCommand::Clear();

		Junia::Renderer::BeginScene(cameraController.GetCamera());

		const glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		const auto flatColorShader = shaderLibrary.Get("FlatColor");
		flatColorShader->Bind();
		std::dynamic_pointer_cast<Junia::OpenGLShader>(flatColorShader)->UploadUniformFloat3("u_Color", squareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(static_cast<float>(x) * 0.11f, static_cast<float>(y) * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Junia::Renderer::Submit(flatColorShader, squareVertexArray, transform);
			}
		}

		const auto textureShader = shaderLibrary.Get("Texture");

		texture->Bind();
		Junia::Renderer::Submit(textureShader, squareVertexArray,
			glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		sdLogoTexture->Bind();
		Junia::Renderer::Submit(textureShader, squareVertexArray,
			glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Junia::Renderer::EndScene();
	}

private:
	Junia::ShaderLibrary shaderLibrary;
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
