// SpriteFont.hpp

#ifndef __SPRITEFONT_HPP__
#define __SPRITEFONT_HPP__

// SAGE Includes
#include <SAGE/IFont.hpp>
// STL Includes
#include <string>

namespace SAGE
{
	struct SpriteFontOptions
	{
		float Size;
		float Spacing;
	};

	class SpriteFont : public ILoadableFont<SpriteFontOptions>
	{
		public:
			SpriteFont();
			~SpriteFont();

			float GetCharacterSpacing(Uint16 p_Character) const override;
			float GetLineSpacing() const override;

			const Texture& GetTexture() const override;
			Rectangle GetCharacterBounds(Uint16 p_Character) const override;

			void MeasureString(const std::string& p_String, Vector2& p_Dimensions) override;

			bool Load(const std::string& p_Filename, const SpriteFontOptions& p_Options) override;
			bool Unload() override;

		private:
			Texture m_Texture;
			float m_Size;
			float m_Spacing;
	};
}

#endif
