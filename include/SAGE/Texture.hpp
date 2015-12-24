// Texture.hpp

#ifndef __SAGE_TEXTURE_HPP__
#define __SAGE_TEXTURE_HPP__

// OpenGL Includes
#if defined __ANDROID__
	#include <GLES3/gl3.h>
#else
	#include <GL/glew.h>
#endif
// SAGE Includes
#include <SAGE/Color.hpp>
#include <SAGE/Surface.hpp>
// STL Includes
#include <string>
#include <vector>

namespace SAGE
{
	enum class Interpolation
	{
		Nearest,
		Linear,
	};

	enum class Wrapping
	{
		Repeat,
		RepeatMirrored,
		ClampToEdge,
		ClampToBorder,
	};

	class Texture
	{
		public:
			Texture();
			~Texture();

			unsigned int GetID() const;
			unsigned int GetWidth() const;
			unsigned int GetHeight() const;
			unsigned int GetBytesPerPixel() const;
			Interpolation GetInterpolation() const;
			Wrapping GetWrapping() const;
			bool GetPixelColor(unsigned int p_X, unsigned int p_Y, Color& p_Color);

			bool FromPixelColors(unsigned int p_Width, unsigned int p_Height, std::vector<Color> p_Colors, Interpolation p_Interpolation = Interpolation::Linear, Wrapping p_Wrapping = Wrapping::Repeat);
			bool Load(const std::string& p_Filename, Interpolation p_Interpolation = Interpolation::Linear, Wrapping p_Wrapping = Wrapping::Repeat);
			bool Unload();

		private:
			bool CreateFromPixelData(void* p_PixelData);
			bool ReadColorDataFromSurface(SDL_Surface* p_Surface, unsigned int p_X, unsigned int p_Y, Uint32& p_Pixel, Color& p_Color);

			bool m_IsLoaded;
			unsigned int m_ID;
			unsigned int m_Width;
			unsigned int m_Height;
			unsigned int m_BytesPerPixel;
			Interpolation m_Interpolation;
			Wrapping m_Wrapping;
			std::vector<Uint32> m_Pixels;
			std::vector<Color> m_Colors;
	};
}

#endif
