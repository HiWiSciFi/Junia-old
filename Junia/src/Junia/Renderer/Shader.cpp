#include "Shader.hpp"

#include <Junia/Renderer/Renderer.hpp>

#ifdef JE_GAPI_SUPPORTED_OPENGL
#include <Junia/Platform/OpenGL/OpenGLShader.hpp>
#endif
#ifdef JE_GAPI_SUPPORTED_VULKAN
#include <Junia/Platform/Vulkan/VulkanShader.hpp>
#endif

namespace Junia
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		#ifdef JE_GAPI_SUPPORTED_OPENGL
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filepath);
		#endif
		#ifdef JE_GAPI_SUPPORTED_VULKAN
		case RendererAPI::API::Vulkan: return std::make_shared<VulkanShader>(filepath);
		#endif
		default: return nullptr;
		}
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		#ifdef JE_GAPI_SUPPORTED_OPENGL
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		#endif
		#ifdef JE_GAPI_SUPPORTED_VULKAN
		case RendererAPI::API::Vulkan: return std::make_shared<VulkanShader>(name, vertexSrc, fragmentSrc);
		#endif
		default: return nullptr;
		}
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		JELOG_BASE_ASSERT(!Exists(name), "Shader \"" JELOG_CSTR "\" already exists in this Library!", name.c_str());
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
		JELOG_BASE_ASSERT(Exists(name), "\"" JELOG_CSTR "\" Shader not found!", name.c_str());
		return shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return shaders.find(name) != shaders.end();
	}
}
