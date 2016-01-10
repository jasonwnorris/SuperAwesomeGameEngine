// SpriteFont.cpp

// SAGE Includes
#include <SAGE/SpriteFont.hpp>
// STL Includes
#include <sstream>
#include <stdio.h>

namespace SAGE
{
	SpriteFont::SpriteFont()
	{
	}

	SpriteFont::~SpriteFont()
	{
		if (m_IsLoaded)
		{
			Unload();
		}
	}

	float SpriteFont::GetCharacterSpacing(Uint16 p_Character) const
	{
		return m_Spacing;
	}

	float SpriteFont::GetLineSpacing() const
	{
		return m_Size;
	}

	const Texture& SpriteFont::GetTexture() const
	{
		return m_Texture;
	}

	Rectangle SpriteFont::GetCharacterBounds(Uint16 p_Character) const
	{
		int textureWidth = m_Texture.GetWidth();
		int textureHeight = m_Texture.GetHeight();
		int index = static_cast<int>(p_Character);

		return Rectangle((index % 16) * (textureWidth / 16), (index / 16) * (textureHeight / 16), textureWidth / 16, textureHeight / 16);
	}

	void SpriteFont::MeasureString(const std::string& p_String, Vector2& p_Dimensions)
	{
		int lineCount = 0;
		int maxLength = 0;
		int glyphWidth = m_Texture.GetWidth() / 16;
		int glyphHeight = m_Texture.GetHeight() / 16;

		std::stringstream ss(p_String);
		std::string line;

		while (std::getline(ss, line))
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

	bool SpriteFont::Load(const std::string& p_Filename, const SpriteFontOptions& p_Options)
	{
		// Currently only supports textures with 16x16 renderer ASCII-ordered glyphs.
		if (!m_Texture.Load(p_Filename))
			return false;

		m_Size = p_Options.Size;
		m_Spacing = p_Options.Spacing;

		return (m_IsLoaded = true);
	}

	bool SpriteFont::Unload()
	{
		if (!m_IsLoaded)
		{
			SDL_Log("[SpriteFont::Unload] SpriteFont already unloaded. Doing nothing.");
		}
		else
		{
			m_Texture.Unload();

			m_IsLoaded = false;
		}

		return true;
	}
}
