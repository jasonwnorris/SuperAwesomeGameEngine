// SpriteFont.cpp

// SAGE Includes
#include <SAGE\SpriteFont.hpp>
// STL Includes
#include <sstream>

namespace SAGE
{
	SpriteFont::SpriteFont()
	{
		mSize = 0.0f;
		mSpacing = 0.0f;
	}

	SpriteFont::~SpriteFont()
	{
	}

	const Texture& SpriteFont::GetTexture() const
	{
		return mTexture;
	}

	float SpriteFont::GetSize() const
	{
		return mSize;
	}

	float SpriteFont::GetSpacing() const
	{
		return mSpacing;
	}

	Rectangle SpriteFont::GetGlyphBounds(char pGlyph) const
	{
		int textureWidth = mTexture.GetWidth();
		int textureHeight = mTexture.GetHeight();
		int index = static_cast<int>(pGlyph);

		return Rectangle((index % 16) * (textureWidth / 16), (index / 16) * (textureHeight / 16), textureWidth / 16, textureHeight / 16);
	}

	void SpriteFont::SetSize(float pSize)
	{
		mSize = pSize;
	}

	void SpriteFont::SetSpacing(float pSpacing)
	{
		mSpacing = pSpacing;
	}

	bool SpriteFont::Load(const std::string& pFilename, float pSize, float pSpacing, Interpolation pInterpolation, Wrapping pWrapping)
	{
		// Currently only supports textures with 16x16 renderer ASCII-ordered glyphs.
		if (!mTexture.Load(pFilename, pInterpolation, pWrapping))
			return false;

		mSize = pSize;
		mSpacing = pSpacing;

		return true;
	}
	
	void SpriteFont::MeasureString(const std::string& pString, Vector2& pDimensions)
	{
		int lineCount = 0;
		int maxLength = 0;
		int glyphWidth = mTexture.GetWidth() / 16;
		int glyphHeight = mTexture.GetHeight() / 16;

		std::stringstream ss(pString);
		std::string line;

		while (std::getline(ss, line, '\n'))
		{
			int length = (int)line.length();
			if (length > maxLength)
			{
				maxLength = length;
			}

			lineCount++;
		}

		pDimensions.X = (float)(maxLength * glyphWidth);
		pDimensions.Y = (float)(lineCount * glyphHeight);
	}
}
