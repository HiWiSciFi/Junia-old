#ifdef JE_GAPI_SUPPORTED_OPENGL

#include "OpenGLTexture.hpp"

#include <stb/stb_image.h>
#include <Junia/Core/Log.hpp>
#include <glad/glad.h>

namespace Junia
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : path(path)
	{
		int w, h, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &w, &h, &channels, 0);
		if (data == nullptr) { JELOG_BASE_ERROR("Image file could not be loaded!"); return; }
		width = static_cast<uint32_t>(w);
		height = static_cast<uint32_t>(h);

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
		glTextureStorage2D(rendererId, 1, glFormat, static_cast<GLsizei>(width), static_cast<GLsizei>(height));

		glTextureParameteri(rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(rendererId, 0, 0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height), dataFormat, GL_UNSIGNED_BYTE, data);

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

#endif
