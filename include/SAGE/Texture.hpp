// Texture.hpp

#ifndef __SAGE_TEXTURE_HPP__
#define __SAGE_TEXTURE_HPP__

// OpenGL Includes
#include <gl\glew.h>
// SAGE Includes
#include <SAGE\Surface.hpp>
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

			bool Load(const std::string& pFilename, Interpolation pInterpolation = Interpolation::Linear, Wrapping pWrapping = Wrapping::Repeat);
			void GetColor(int pX, int pY, Uint8& pRed, Uint8& pGreen, Uint8& pBlue, Uint8& pAlpha);

		private:
			SDL_Surface* mSurface;
			unsigned int mWidth;
			unsigned int mHeight;
			unsigned int mBPP;
			unsigned int mID;
	};
}

#endif
