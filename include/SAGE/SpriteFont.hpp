// SpriteFont.hpp

#ifndef __SPRITEFONT_HPP__
#define __SPRITEFONT_HPP__

// SAGE Includes
#include <SAGE\Texture.hpp>
#include <SAGE\Rectangle.hpp>
#include <SAGE\Vector2.hpp>
// STL Includes
#include <string>

namespace SAGE
{
	class SpriteFont
	{
		public:
			SpriteFont();
			~SpriteFont();

			const Texture& GetTexture() const;
			float GetSize() const;
			float GetSpacing() const;
			Rectangle GetGlyphBounds(char pGlyph) const;

			void SetSize(float pSize);
			void SetSpacing(float pSpacing);

			bool Load(const std::string& pFilename, float pSize, float pSpacing, Interpolation pInterpolation = Interpolation::Linear, Wrapping pWrapping = Wrapping::Repeat);
			void MeasureString(const std::string& pString, Vector2& pDimensions);

		private:
			Texture mTexture;
			float mSize;
			float mSpacing;
	};
}

#endif
