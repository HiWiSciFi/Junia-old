#include "Font.hpp"

//#include <stb/stb_truetype.h>
//#include <stb/stb_image.h>
//#include <stb/stb_image_write.h>
#include <Junia/Platform/Platform.hpp>
#include <Junia/Core/Log.hpp>

#define FT_CONFIG_OPTION_ERROR_STRINGS
#include <ft2build.h>
#include FT_FREETYPE_H

namespace Junia
{
	static FT_Library ftlib;

	Ref<Font> Font::Create(const std::string& filepath)
	{
		return CreateRef<Font>(filepath);
	}

	Font::Font(const std::string& filepath)
	{
		FT_Error ftError;

		// Freetype 2 initialization
		static bool ftinitialized = false;
		if (!ftinitialized)
		{
			if (ftError = FT_Init_FreeType(&ftlib))
			{
				JELOG_BASE_CRIT("Freetype could not be initialized! Error: " JELOG_CSTR, FT_Error_String(ftError));
				return;
			}
			else
			{
				int mj, mn, p;
				FT_Library_Version(ftlib, &mj, &mn, &p);
				std::stringstream ss;
				ss << mj << '.' << mn << '.' << p;
				JELOG_BASE_INFO("Freetype Version " JELOG_CSTR " initialized!", ss.str().c_str());
			}
		}

		// Load Font

		if (filepath.empty()) return;

		// From the docs:
		// To know how many faces a given font file contains, set face_index to -1, then check the value
		// of face->num_faces, which indicates how many faces are embedded in the font file.
		FT_Face face = reinterpret_cast<FT_Face>(fontFace);
		ftError = FT_New_Face(ftlib, filepath.c_str(), 0, &face);
		if (ftError)
		{
			JELOG_BASE_ERROR("Failed to load font face! Error: " JELOG_CSTR, FT_Error_String(ftError));
			return;
		}
	}

	Font::~Font()
	{
		FT_Done_Face(reinterpret_cast<FT_Face>(fontFace));
	}

	Ref<Texture2D> Font::GetTextureFromString(const std::string& text)
	{
		FT_Error ftError;
		FT_Face face = reinterpret_cast<FT_Face>(fontFace);
		uint32_t cc;
		FT_UInt glyph_index;

		ftError = FT_Set_Pixel_Sizes(face, 0, 48);
		if (ftError)
		{
			JELOG_BASE_ERROR("Failed to size font! Error: " JELOG_CSTR, FT_Error_String(ftError));
			return nullptr;
		}

		for (size_t i = 0; i < text.size(); i++)
		{
			cc = text.at(i);
			// FT_Get_Char_Index - FT_Load_Glyph - FT_Render_Glyph | all in one call
			ftError = FT_Load_Char(face, cc, FT_LOAD_RENDER);
			if (ftError)
			{
				JELOG_BASE_ERROR(
					"Glyph for character \'" JELOG_CHAR "\' could not be loaded! Error: " JELOG_CSTR,
					cc,
					FT_Error_String(ftError));
				continue;
			}

		}

		return Texture2D::Create(10, 10);
	}
}
