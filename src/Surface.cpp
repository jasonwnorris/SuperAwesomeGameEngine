// Surface.cpp

// SDL Includes
#include <SDL2/SDL_image.h>
// SAGE Includes
#include <SAGE/Console.hpp>
#include <SAGE/Surface.hpp>

namespace SAGE
{
	Surface::Surface(Uint32 p_Flags, int p_Width, int p_Height, int p_Depth, Uint32 p_RedMask, Uint32 p_GreenMask, Uint32 p_BlueMask, Uint32 p_AlphaMask)
	{
		// Create the surface.
		m_Surface = SDL_CreateRGBSurface(p_Flags, p_Width, p_Height, p_Depth, p_RedMask, p_GreenMask, p_BlueMask, p_AlphaMask);
	}

	Surface::Surface(void* p_Pixels, int p_Width, int p_Height, int p_Depth, int p_Pitch, Uint32 p_RedMask, Uint32 p_GreenMask, Uint32 p_BlueMask, Uint32 p_AlphaMask)
	{
		// Create the surface.
		m_Surface = SDL_CreateRGBSurfaceFrom(p_Pixels, p_Width, p_Height, p_Depth, p_Pitch, p_RedMask, p_GreenMask, p_BlueMask, p_AlphaMask);
	}

	Surface::Surface(const std::string& p_Filename)
	{
		// Create the surface from a loaded image file.
		m_Surface = IMG_Load(p_Filename.c_str());
	}

	Surface::~Surface()
	{
		SDL_FreeSurface(m_Surface);
	}

	SDL_Surface* Surface::GetC() const
	{
		// Return C structure.
		return m_Surface;
	}

	int Surface::SetColorKey(Uint32 p_Key)
	{
		// Set a color key on the surface.
		int code = SDL_SetColorKey(m_Surface, SDL_TRUE, p_Key);
		if (code < 0)
			Console::WriteLine("[Surface::SetColorKey] Failed to set color key to surface: %s", SDL_GetError());

		return code;
	}
}
