// Texture.hpp

#ifndef __SAGE_TEXTURE_HPP__
#define __SAGE_TEXTURE_HPP__

// OpenGL Includes
#include <GL/glew.h>
// SAGE Includes
#include <SAGE/Surface.hpp>
// STL Includes
#include <string>

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

			unsigned int GetWidth() const;
			unsigned int GetHeight() const;
			unsigned int GetBPP() const;
			unsigned int GetID() const;
			Uint32* GetPixels() const;
			SDL_PixelFormat* GetFormat() const;

			bool Load(const std::string& p_Filename, Interpolation p_Interpolation = Interpolation::Linear, Wrapping p_Wrapping = Wrapping::Repeat);
			void GetColor(int p_X, int p_Y, Uint8& p_Red, Uint8& p_Green, Uint8& p_Blue, Uint8& p_Alpha);

		private:
			SDL_Surface* m_Surface;
			unsigned int m_Width;
			unsigned int m_Height;
			unsigned int m_BPP;
			unsigned int m_ID;
	};
}

#endif
