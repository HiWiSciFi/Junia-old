#pragma once

#include <Junia/Renderer/Texture.hpp>

namespace Junia
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		explicit OpenGLTexture2D(const std::string& path);
		~OpenGLTexture2D() override;

		[[nodiscard]] uint32_t GetWidth() const override { return width; }
		[[nodiscard]] uint32_t GetHeight() const override { return height; }

		void Bind(uint32_t slot) const override;

	private:
		std::string path;
		uint32_t width = 0;
		uint32_t height = 0;
		uint32_t rendererId = 0;
	};
}