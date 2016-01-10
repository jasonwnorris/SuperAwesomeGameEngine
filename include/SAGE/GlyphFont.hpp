// GlyphFont.hpp

#ifndef __GLYPHFONT_HPP__
#define __GLYPHFONT_HPP__

// SAGE Includes
#include <SAGE/IFont.hpp>
// SDL Includes
#if defined __ANDROID__
	#include <SDL_ttf.h>
#else
	#include <SDL2/SDL_ttf.h>
#endif
// STL Includes
#include <string>

namespace SAGE
{
	enum class GlyphFontStyle : int
	{
		Normal = TTF_STYLE_NORMAL,
		Bold = TTF_STYLE_BOLD,
		Italic = TTF_STYLE_ITALIC,
		Underline = TTF_STYLE_UNDERLINE,
		Strikethrough = TTF_STYLE_STRIKETHROUGH
	};

	enum class GlyphFontHinting : int
	{
		Normal = TTF_HINTING_NORMAL,
		Light = TTF_HINTING_LIGHT,
		Mono = TTF_HINTING_MONO,
		None = TTF_HINTING_NONE
	};

	struct GlyphFontOptions
	{
		int Size;
		GlyphFontStyle Style;
		GlyphFontHinting Hinting;
		int Outline;
		bool UseKerning;
	};

	struct Glyph
	{
		Uint16 Character;
		int Index;
		int MinX;
		int MaxX;
		int MinY;
		int MaxY;
		int Advance;
		int SpacialWidth;
		int SpacialHeight;
		int VisualX;
		int VisualY;
		int VisualWidth;
		int VisualHeight;
		SDL_Surface* Surface;

		bool operator==(const Glyph& other)
		{
			return this->Character == other.Character && this->Index == other.Index;
		}
	};

	class GlyphFont : public SAGE::ILoadableFont<GlyphFontOptions>
	{
		public:
			GlyphFont();
			~GlyphFont();

			float GetCharacterSpacing(Uint16 p_Character) const override;
			float GetLineSpacing() const override;

			const SAGE::Texture& GetTexture() const override;
			SAGE::Rectangle GetCharacterBounds(Uint16 p_Character) const override;

			void MeasureString(const std::string& p_String, SAGE::Vector2& p_Dimensions) override;

			bool Load(const std::string& p_Filename, const GlyphFontOptions& p_Options) override;
			bool Unload() override;

		private:
			int HeuristicWidth();
			int MakeValidTextureSize(int p_Value, bool p_IsPOT = true);
			SDL_Surface* TrimSurface(SDL_Surface* surface);
			void GetPixelColor(SDL_Surface* surface, int x, int y, Uint8& red, Uint8& green, Uint8& blue, Uint8& alpha);

		private:
			SAGE::Texture m_Texture;
			int m_Height;
			int m_Ascent;
			int m_Descent;
			int m_LineSkip;
			long m_Faces;
			bool m_IsFixedWidth;
			std::string m_FaceFamilyName;
			std::string m_FaceStyleName;
			std::vector<Glyph> m_Glyphs;
	};
}

#endif
