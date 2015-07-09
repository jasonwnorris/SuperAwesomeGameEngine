// SpriteFont.cpp

// SAGE Includes
#include <SAGE\SpriteFont.hpp>
// STL Includes
#include <sstream>

namespace SAGE
{
	SpriteFont::SpriteFont()
	{
		m_Size = 0.0f;
		m_Spacing = 0.0f;
	}

	SpriteFont::~SpriteFont()
	{
	}

	const Texture& SpriteFont::GetTexture() const
	{
		return m_Texture;
	}

	float SpriteFont::GetSize() const
	{
		return m_Size;
	}

	float SpriteFont::GetSpacing() const
	{
		return m_Spacing;
	}

	Rectangle SpriteFont::GetGlyphBounds(char p_Glyph) const
	{
		int textureWidth = m_Texture.GetWidth();
		int textureHeight = m_Texture.GetHeight();
		int index = static_cast<int>(p_Glyph);

		return Rectangle((index % 16) * (textureWidth / 16), (index / 16) * (textureHeight / 16), textureWidth / 16, textureHeight / 16);
	}

	void SpriteFont::SetSize(float p_Size)
	{
		m_Size = p_Size;
	}

	void SpriteFont::SetSpacing(float p_Spacing)
	{
		m_Spacing = p_Spacing;
	}

	bool SpriteFont::Load(const std::string& p_Filename, float p_Size, float p_Spacing, Interpolation p_Interpolation, Wrapping p_Wrapping)
	{
		// Currently only supports textures with 16x16 renderer ASCII-ordered glyphs.
		if (!m_Texture.Load(p_Filename, p_Interpolation, p_Wrapping))
			return false;

		m_Size = p_Size;
		m_Spacing = p_Spacing;

		return true;
	}
	
	void SpriteFont::MeasureString(const std::string& p_String, Vector2& p_Dimensions)
	{
		int lineCount = 0;
		int maxLength = 0;
		int glyphWidth = m_Texture.GetWidth() / 16;
		int glyphHeight = m_Texture.GetHeight() / 16;

		std::stringstream ss(p_String);
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

		p_Dimensions.X = (float)(maxLength * glyphWidth);
		p_Dimensions.Y = (float)(lineCount * glyphHeight);
	}
}
