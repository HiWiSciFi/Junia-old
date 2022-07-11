#pragma once

#include <string>
#include <glm/glm.hpp>
#include <Junia/Core/Base.hpp>
#include <unordered_map>

namespace Junia
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind()   const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& vname, int value) = 0;
		virtual void SetFloat(const std::string& vname, float value) = 0;
		virtual void SetFloat2(const std::string& vname, const glm::vec2& values) = 0;
		virtual void SetFloat3(const std::string& vname, const glm::vec3& values) = 0;
		virtual void SetFloat4(const std::string& vname, const glm::vec4& values) = 0;
		virtual void SetMat3(const std::string& vname, const glm::mat3& matrix) = 0;
		virtual void SetMat4(const std::string& vname, const glm::mat4& matrix) = 0;

		[[nodiscard]] virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	};

	class ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name, const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		Ref<Shader> Get(const std::string& name);

		[[nodiscard]] bool Exists(const std::string& name) const;

	private:
		std::unordered_map<std::string, Ref<Shader>> shaders;
	};
}
