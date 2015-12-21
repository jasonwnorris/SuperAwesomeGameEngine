// SpriteFont.hpp

#ifndef __SPRITEFONT_HPP__
#define __SPRITEFONT_HPP__

// SAGE Includes
#include <SAGE/Texture.hpp>
#include <SAGE/Rectangle.hpp>
#include <SAGE/Vector2.hpp>
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
			Rectangle GetGlyphBounds(char p_Glyph) const;

			void SetSize(float p_Size);
			void SetSpacing(float p_Spacing);

			bool Load(const std::string& p_Filename, float p_Size, float p_Spacing, Interpolation p_Interpolation = Interpolation::Linear, Wrapping p_Wrapping = Wrapping::Repeat);
			bool Unload();
			void MeasureString(const std::string& p_String, Vector2& p_Dimensions);

		private:
			Texture m_Texture;
			float m_Size;
			float m_Spacing;
			bool m_IsLoaded;
	};
}

#endif
