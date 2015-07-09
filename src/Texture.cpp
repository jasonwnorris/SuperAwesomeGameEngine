// Texture.cpp

// SDL Includes
#include <SDL2\SDL_image.h>
// SAGE Includes
#include <SAGE\Texture.hpp>

namespace SAGE
{
	Texture::Texture()
	{
		mID = -1;
	}

	Texture::~Texture()
	{
		// Free the surface.
		if (mSurface != nullptr)
		{
			SDL_FreeSurface(mSurface);
		}

		// Delete the texture.
		if (mID != -1)
		{
			glDeleteTextures(1, &mID);
		}
	}

	unsigned int Texture::GetWidth() const
	{
		return mWidth;
	}

	unsigned int Texture::GetHeight() const
	{
		return mHeight;
	}

	unsigned int Texture::GetBPP() const
	{
		return mBPP;
	}

	unsigned int Texture::GetID() const
	{
		return mID;
	}

	Uint32* Texture::GetPixels() const
	{
		return (Uint32*)mSurface->pixels;
	}

	SDL_PixelFormat* Texture::GetFormat() const
	{
		return mSurface->format;
	}

	bool Texture::Load(const std::string& pFilename, Interpolation pInterpolation, Wrapping pWrapping)
	{
		// Load the surface.
		mSurface = IMG_Load(pFilename.c_str());
		if (mSurface == nullptr)
		{
			SDL_Log("[Texture::Load] Failed to load image file \"%s\": %s", pFilename, SDL_GetError());
			return false;
		}

		// Grab width and height.
		mWidth = mSurface->w;
		mHeight = mSurface->h;
		if ((mWidth & (mWidth - 1)) != 0)
			SDL_LogWarn(SDL_LOG_PRIORITY_WARN, "[Texture::Load] Width is not power of two.");
		if ((mHeight & (mHeight - 1)) != 0)
			SDL_LogWarn(SDL_LOG_PRIORITY_WARN, "[Texture::Load] Height is not power of two.");

		// Determine color mode.
		GLenum format;
		GLint colorCount = mSurface->format->BytesPerPixel;
		if (colorCount == 4)
		{
			if (mSurface->format->Rmask == 0x000000ff)
				format = GL_RGBA;
			else
				format = GL_BGRA;
		}
		else if (colorCount == 3)
		{
			if (mSurface->format->Rmask == 0x000000ff)
				format = GL_RGB;
			else
				format = GL_BGR;
		}
		else
		{
			SDL_LogWarn(SDL_LOG_PRIORITY_WARN, "[Texture::Load] Image is not true color.");
		}

		// Generate and create the texture.
		glGenTextures(1, &mID);
		glBindTexture(GL_TEXTURE_2D, mID);
		glTexImage2D(GL_TEXTURE_2D, 0, colorCount, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, mSurface->pixels);

		// Set scaling interpolation.
		switch (pInterpolation)
		{
			case Interpolation::Nearest:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				break;
			case Interpolation::Linear:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				break;
		}

		// Set edge wrapping.
		switch (pWrapping)
		{
			case Wrapping::Repeat:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				break;
			case Wrapping::RepeatMirrored:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
				break;
			case Wrapping::ClampToEdge:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				break;
			case Wrapping::ClampToBorder:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
				static float color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
				glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
				break;
		}

		// Unbind the texture.
		glBindTexture(GL_TEXTURE_2D, 0);

		return true;
	}

	void Texture::GetColor(int pX, int pY, Uint8& pRed, Uint8& pGreen, Uint8& pBlue, Uint8& pAlpha)
	{
		Uint8* pixel = (Uint8*)mSurface->pixels + pY * mSurface->pitch + pX * mSurface->format->BytesPerPixel;
		Uint32 color = 0;

		switch (mSurface->format->BytesPerPixel)
		{
		case 1:
			color = *pixel;
			break;
		case 2:
			color = *(Uint16*)pixel;
			break;
		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				color = pixel[0] << 16 | pixel[1] << 8 | pixel[2];
			else
				color = pixel[0] | pixel[1] << 8 | pixel[2] << 16;
			break;
		case 4:
			color = *(Uint32*)pixel;
			break;
		default:
			color = 0;
			break;
		}

		SDL_GetRGBA(color, mSurface->format, &pRed, &pGreen, &pBlue, &pAlpha);
	}
}
