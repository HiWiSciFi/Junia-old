#pragma once

#include <Junia/Core/Base.hpp>
#include <string>
#include <Junia/Renderer/Texture.hpp>

namespace Junia
{
	class Font
	{
	public:
		static Ref<Font> Create(const std::string& filepath);
		Font(const std::string& filepath);
		~Font();

		Ref<Texture2D> GetTextureFromString(const std::string& text);

	private:
		void* fontFace = nullptr;
		void* fontInfo = nullptr;
		std::string fontBuffer;
	};
}
