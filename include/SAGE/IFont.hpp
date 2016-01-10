// IFont.hpp

#ifndef __IFONT_HPP__
#define __IFONT_HPP__

// SAGE Includes
#include <SAGE/ILoadable.hpp>
#include <SAGE/Rectangle.hpp>
#include <SAGE/Texture.hpp>
#include <SAGE/Vector2.hpp>
// STL Includes
#include <string>

namespace SAGE
{
	class IFont
	{
		public:
			IFont() = default;
			virtual ~IFont() = default;

			virtual float GetCharacterSpacing(Uint16 p_Character = 0) const = 0;
			virtual float GetLineSpacing() const = 0;

			virtual const Texture& GetTexture() const = 0;
			virtual Rectangle GetCharacterBounds(Uint16 p_Character) const = 0;

			virtual void MeasureString(const std::string& p_String, Vector2& p_Dimensions) = 0;
	};

	template<typename T> class ILoadableFont : public ILoadable<T>, public IFont
	{
		public:
			ILoadableFont() : IFont() { }
			virtual ~ILoadableFont() = default;
	};
}

#endif
