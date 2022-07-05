#pragma once

#include <Junia/Renderer/Texture.hpp>

namespace Junia
{
	class VulkanTexture2D : public Texture2D
	{
	public:
		explicit VulkanTexture2D(const std::string& path);
		~VulkanTexture2D();

		uint32_t GetWidth() const override { return width; }
		uint32_t GetHeight() const override { return height; }

		void Bind(uint32_t slot) const override;

	private:
		std::string path;
		uint32_t width, height;
	};
}
