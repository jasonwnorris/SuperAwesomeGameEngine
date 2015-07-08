// SpriteFont.hpp

#ifndef __SPRITEFONT_HPP__
#define __SPRITEFONT_HPP__

// HGF Includes
#include <HGF\Texture.hpp>
#include <HGF\Rectangle.hpp>
#include <HGF\Vector2.hpp>
// STL Includes
#include <string>

namespace SAGE
{
	class SpriteFont
	{
		public:
			SpriteFont();
			~SpriteFont();

			const HGF::Texture& GetTexture() const;
			float GetSize() const;
			float GetSpacing() const;
			HGF::Rectangle GetGlyphBounds(char pGlyph) const;

			void SetSize(float pSize);
			void SetSpacing(float pSpacing);

			bool Load(const std::string& pFilename, float pSize, float pSpacing, HGF::Interpolation pInterpolation = HGF::Interpolation::Linear, HGF::Wrapping pWrapping = HGF::Wrapping::Repeat);
			void MeasureString(const std::string& pString, HGF::Vector2& pDimensions);

		private:
			HGF::Texture mTexture;
			float mSize;
			float mSpacing;
	};
}

#endif