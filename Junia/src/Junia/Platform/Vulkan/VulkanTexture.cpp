#include "VulkanTexture.hpp"

namespace Junia
{
    VulkanTexture2D::VulkanTexture2D(const std::string& path) : width(0), height(0)
    {
    }

	VulkanTexture2D::~VulkanTexture2D()
	{
	}

	void VulkanTexture2D::Bind(uint32_t slot) const
	{
	}
}
