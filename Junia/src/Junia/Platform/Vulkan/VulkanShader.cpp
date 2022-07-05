#include "VulkanShader.hpp"

namespace Junia
{
	VulkanShader::VulkanShader(const std::string& filepath)
	{
	}
	VulkanShader::VulkanShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
	}

	VulkanShader::~VulkanShader()
	{
	}

	void VulkanShader::Bind() const
	{
	}

	void VulkanShader::Unbind() const
	{
	}

	void VulkanShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values)
	{
	}

	void VulkanShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
	}
}
