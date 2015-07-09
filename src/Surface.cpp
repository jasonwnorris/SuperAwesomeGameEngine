// Surface.cpp

// SDL Includes
#include <SDL2\SDL_image.h>
// SAGE Includes
#include <SAGE\Console.hpp>
#include <SAGE\Surface.hpp>

namespace SAGE
{
	Surface::Surface(Uint32 pFlags, int pWidth, int pHeight, int pDepth, Uint32 pRedMask, Uint32 pGreenMask, Uint32 pBlueMask, Uint32 pAlphaMask)
	{
		// Create the surface.
		mSurface = SDL_CreateRGBSurface(pFlags, pWidth, pHeight, pDepth, pRedMask, pGreenMask, pBlueMask, pAlphaMask);
	}

	Surface::Surface(void* pPixels, int pWidth, int pHeight, int pDepth, int pPitch, Uint32 pRedMask, Uint32 pGreenMask, Uint32 pBlueMask, Uint32 pAlphaMask)
	{
		// Create the surface.
		mSurface = SDL_CreateRGBSurfaceFrom(pPixels, pWidth, pHeight, pDepth, pPitch, pRedMask, pGreenMask, pBlueMask, pAlphaMask);
	}

	Surface::Surface(const std::string& pFilename)
	{
		// Create the surface from a loaded image file.
		mSurface = IMG_Load(pFilename.c_str());
	}

	Surface::~Surface()
	{
		SDL_FreeSurface(mSurface);
	}

	SDL_Surface* Surface::GetC() const
	{
		// Return C structure.
		return mSurface;
	}

	int Surface::SetColorKey(Uint32 pKey)
	{
		// Set a color key on the surface.
		int code = SDL_SetColorKey(mSurface, SDL_TRUE, pKey);
		if (code < 0)
			Console::WriteLine("[Surface::SetColorKey] Failed to set color key to surface: %s", SDL_GetError());

		return code;
	}
}
