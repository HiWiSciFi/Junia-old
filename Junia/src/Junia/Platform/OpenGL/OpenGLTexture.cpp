#include "OpenGLTexture.hpp"

#include <stb/stb_image.h>
#include <Junia/Log.hpp>
#include <glad/glad.h>

namespace Junia
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : path(path), width(0), height(0), rendererId(0)
	{
		int w, h, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &w, &h, &channels, 0);
		if (data == NULL) { JELOG_BASE_ERROR("Image file could not be loaded!"); return; }
		width = w;
		height = h;

		GLenum glFormat = 0, dataFormat = 0;
		switch (channels)
		{
		case 3:
			glFormat = GL_RGB8;
			dataFormat = GL_RGB;
			break;
		case 4:
			glFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
			break;
		default:
			JELOG_BASE_ERROR("Texture format not supported! Falling back to 8-bit RGBA...");
			glFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
			break;
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererId);
		glTextureStorage2D(rendererId, 1, glFormat, width, height);

		glTextureParameteri(rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(rendererId, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &rendererId);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, rendererId);
	}
}
