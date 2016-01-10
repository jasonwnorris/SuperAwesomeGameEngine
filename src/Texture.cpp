// Texture.cpp

// SDL Includes
#if defined __ANDROID__
	#include <SDL_image.h>
#else
	#include <SDL2/SDL_image.h>
#endif
// SAGE Includes
#include <SAGE/Math.hpp>
#include <SAGE/Texture.hpp>

namespace SAGE
{
	Texture::Texture()
	{
		m_ID = -1;
		m_IsLoaded = false;
	}

	Texture::~Texture()
	{
		if (m_IsLoaded)
		{
			Unload();
		}
	}

	unsigned int Texture::GetID() const
	{
		return m_ID;
	}

	unsigned int Texture::GetWidth() const
	{
		return m_Width;
	}

	unsigned int Texture::GetHeight() const
	{
		return m_Height;
	}

	unsigned int Texture::GetBytesPerPixel() const
	{
		return m_BytesPerPixel;
	}

	Interpolation Texture::GetInterpolation() const
	{
		return m_Interpolation;
	}

	Wrapping Texture::GetWrapping() const
	{
		return m_Wrapping;
	}

	bool Texture::GetPixelColor(unsigned int p_X, unsigned int p_Y, Color& p_Color)
	{
		// Check if within bounds.
		if (p_X >= m_Width || p_Y >= m_Height)
		{
			SDL_Log("[Texture::GetPixelColor] Coordinates are out of texture bounds.");
			return false;
		}

		p_Color = m_Colors[p_X + p_Y * m_Width];

		return true;
	}

	bool Texture::FromPixelColors(unsigned int p_Width, unsigned int p_Height, std::vector<Color> p_Colors, Interpolation p_Interpolation, Wrapping p_Wrapping)
	{
		// Check if already loaded.
		if (m_IsLoaded)
		{
			SDL_Log("[Texture::FromPixelColors] Texture is already loaded.");
			return false;
		}

		// Collect metrics.
		m_Width = p_Width;
		m_Height = p_Height;
		m_BytesPerPixel = 4;
		m_Interpolation = p_Interpolation;
		m_Wrapping = p_Wrapping;

		// Copy colors to cpmposite pixels.
		for (const auto& color : p_Colors)
		{
			m_Colors.push_back(color);

			Uint32 composite = color.GetAsComposite();
			m_Pixels.push_back(composite);

			/*
			SDL_Log("Added Composite Color: { R: %d, G: %d, B: %d, A: %d } = %u",
				color.GetRedAsByte(),
				color.GetGreenAsByte(),
				color.GetBlueAsByte(),
				color.GetAlphaAsByte(),
				composite);
			*/
		}

		// Create the texture.
		if (!CreateFromPixelData(static_cast<void*>(&m_Pixels.front())))
		{
			return false;
		}

		return (m_IsLoaded = true);
	}

	bool Texture::Load(const std::string& p_Filename, Interpolation p_Interpolation, Wrapping p_Wrapping)
	{
		// Check if already loaded.
		if (m_IsLoaded)
		{
			SDL_Log("[Texture::Load] Texture is already loaded.");
			return false;
		}

		// Load the surface.
		SDL_Surface* surface = IMG_Load(p_Filename.c_str());
		if (surface == nullptr)
		{
			SDL_Log("[Texture::Load] Failed to load image file \"%s\": %s", p_Filename.c_str(), SDL_GetError());
			return false;
		}

		// Collect metrics.
		m_Width = surface->w;
		m_Height = surface->h;
		m_BytesPerPixel = surface->format->BytesPerPixel;
		m_Interpolation = p_Interpolation;
		m_Wrapping = p_Wrapping;

		// Gather pixel colors.
		Uint32 pixel;
		Color color;
		for (int y = 0; y < m_Height; ++y)
		{
			for (int x = 0; x < m_Width; ++x)
			{
				if (ReadColorDataFromSurface(surface, x, y, pixel, color))
				{
					m_Pixels.push_back(pixel);
					m_Colors.push_back(color);
				}
			}
		}

		// Create the texture.
		if (!CreateFromPixelData(surface->pixels))
		{
			return false;
		}

		// Free the loaded surface.
		SDL_FreeSurface(surface);

		return (m_IsLoaded = true);
	}

	bool Texture::Unload()
	{
		if (!m_IsLoaded)
		{
			SDL_Log("[Texture::Unload] Texture already unloaded. Doing nothing.");
		}
		else
		{
			// Delete the texture.
			if (m_ID != -1)
			{
				glDeleteTextures(1, &m_ID);
			}

			m_Pixels.clear();
			m_Colors.clear();

			m_IsLoaded = false;
		}

		return true;
	}

	bool Texture::CreateFromPixelData(void* p_PixelData)
	{
		// Check dimensions.
		if (!Math::IsPO2(m_Width))
		{
			SDL_LogWarn(SDL_LOG_PRIORITY_WARN, "[Texture::CreateFromPixelData] Width is not a power of two.");
		}
		if (!Math::IsPO2(m_Height))
		{
			SDL_LogWarn(SDL_LOG_PRIORITY_WARN, "[Texture::CreateFromPixelData] Height is not a power of two.");
		}

		// Determine color mode.
		GLenum format = 0;
		switch (m_BytesPerPixel)
		{
			case 3:
				format = GL_RGB;
				break;
			case 4:
				format = GL_RGBA;
				break;
			default:
				SDL_LogWarn(SDL_LOG_PRIORITY_WARN, "[Texture::CreateFromPixelData] Pixel data does not use true color.");
				return false;
		}

		// Generate and create the texture.
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, p_PixelData);

		// Set scaling interpolation.
		switch (m_Interpolation)
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
		switch (m_Wrapping)
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

	bool Texture::ReadColorDataFromSurface(SDL_Surface* p_Surface, unsigned int p_X, unsigned int p_Y, Uint32& p_Pixel, Color& p_Color)
	{
		// Check if within bounds.
		if (p_X >= m_Width || p_Y >= m_Height)
		{
			SDL_Log("[Texture::ReadColorDataFromSurface] Coordinates are out of texture bounds.");
			return false;
		}

		Uint8* pointer = (Uint8*)p_Surface->pixels + p_Y * p_Surface->pitch + p_X * m_BytesPerPixel;

		switch (m_BytesPerPixel)
		{
			case 1:
				p_Pixel = *pointer;
				break;
			case 2:
				p_Pixel = *(Uint16*)pointer;
				break;
			case 3:
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
					p_Pixel = pointer[0] << 16 | pointer[1] << 8 | pointer[2];
#else
					p_Pixel = pointer[0] | pointer[1] << 8 | pointer[2] << 16;
#endif
				break;
			case 4:
				p_Pixel = *(Uint32*)pointer;
				break;
			default:
				SDL_LogWarn(SDL_LOG_PRIORITY_WARN, "[Texture::ReadColorDataFromSurface] Pixel data has unknown color format.");
				return false;
		}

		p_Color.SetFromComposite(p_Pixel);

		return false;
	}
}
