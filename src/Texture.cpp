// Texture.cpp

// SDL Includes
#include <SDL2/SDL_image.h>
// SAGE Includes
#include <SAGE/Texture.hpp>

namespace SAGE
{
	Texture::Texture()
	{
		m_ID = -1;
	}

	Texture::~Texture()
	{
		// Free the surface.
		if (m_Surface != nullptr)
		{
			SDL_FreeSurface(m_Surface);
		}

		// Delete the texture.
		if (m_ID != -1)
		{
			glDeleteTextures(1, &m_ID);
		}
	}

	unsigned int Texture::GetWidth() const
	{
		return m_Width;
	}

	unsigned int Texture::GetHeight() const
	{
		return m_Height;
	}

	unsigned int Texture::GetBPP() const
	{
		return m_BPP;
	}

	unsigned int Texture::GetID() const
	{
		return m_ID;
	}

	Uint32* Texture::GetPixels() const
	{
		return (Uint32*)m_Surface->pixels;
	}

	SDL_PixelFormat* Texture::GetFormat() const
	{
		return m_Surface->format;
	}

	bool Texture::Load(const std::string& p_Filename, Interpolation p_Interpolation, Wrapping p_Wrapping)
	{
		// Load the surface.
		m_Surface = IMG_Load(p_Filename.c_str());
		if (m_Surface == nullptr)
		{
			SDL_Log("[Texture::Load] Failed to load image file \"%s\": %s", p_Filename.c_str(), SDL_GetError());
			return false;
		}

		// Grab width and height.
		m_Width = m_Surface->w;
		m_Height = m_Surface->h;
		if ((m_Width & (m_Width - 1)) != 0)
			SDL_LogWarn(SDL_LOG_PRIORITY_WARN, "[Texture::Load] Width is not power of two.");
		if ((m_Height & (m_Height - 1)) != 0)
			SDL_LogWarn(SDL_LOG_PRIORITY_WARN, "[Texture::Load] Height is not power of two.");

		// Determine color mode.
		GLenum format = 0;
		GLint bpp = m_Surface->format->BytesPerPixel;
		if (bpp == 4)
		{
			if (m_Surface->format->Rmask == 0x000000ff)
				format = GL_RGBA;
			else
				format = GL_BGRA;
		}
		else if (bpp == 3)
		{
			if (m_Surface->format->Rmask == 0x000000ff)
				format = GL_RGB;
			else
				format = GL_BGR;
		}
		else
		{
			SDL_LogWarn(SDL_LOG_PRIORITY_WARN, "[Texture::Load] Image is not true color.");
		}

		// Generate and create the texture.
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, bpp, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_Surface->pixels);

		// Set scaling interpolation.
		switch (p_Interpolation)
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
		switch (p_Wrapping)
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

	void Texture::GetColor(int p_X, int p_Y, Uint8& p_Red, Uint8& p_Green, Uint8& p_Blue, Uint8& p_Alpha)
	{
		Uint8* pixel = (Uint8*)m_Surface->pixels + p_Y * m_Surface->pitch + p_X * m_Surface->format->BytesPerPixel;
		Uint32 color = 0;

		switch (m_Surface->format->BytesPerPixel)
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

		SDL_GetRGBA(color, m_Surface->format, &p_Red, &p_Green, &p_Blue, &p_Alpha);
	}
}
