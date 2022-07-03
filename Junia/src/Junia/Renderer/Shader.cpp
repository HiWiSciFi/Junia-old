#include "Shader.hpp"

#include <Junia/Renderer/Renderer.hpp>

#include <Junia/Platform/OpenGL/OpenGLShader.hpp>
#include <Junia/Platform/Vulkan/VulkanShader.hpp>

namespace Junia
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filepath);
		case RendererAPI::API::Vulkan: return std::make_shared<VulkanShader>(filepath);
		default: return nullptr;
		}
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		case RendererAPI::API::Vulkan: return std::make_shared<VulkanShader>(name, vertexSrc, fragmentSrc);
		default: return nullptr;
		}
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		if (Exists(name)) JELOG_BASE_ERROR("Shader already exists!");
		shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		if (!Exists(name)) JELOG_BASE_ERROR("\"" JELOG_CSTR "\" Shader not found!", name.c_str());
		return shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return shaders.find(name) != shaders.end();
	}
}
