// Surface.hpp

#ifndef __SAGE_SURFACE_HPP__
#define __SAGE_SURFACE_HPP__

// SDL Includes
#include <SDL2\SDL.h>
// STL Includes
#include <string>

namespace SAGE
{
	class Surface
	{
		public:
			Surface(Uint32 pFlags, int pWidth, int pHeight, int pDepth, Uint32 pRedMask, Uint32 pGreenMask, Uint32 pBlueMask, Uint32 pAlphaMask);
			Surface(void* pPixels, int pWidth, int pHeight, int pDepth, int pPitch, Uint32 pRedMask, Uint32 pGreenMask, Uint32 pBlueMask, Uint32 pAlphaMask);
			Surface(const std::string& pFilename);
			~Surface();

			SDL_Surface* GetC() const;

			int SetColorKey(Uint32 pKey);

		private:
			SDL_Surface* mSurface;
	};
}

#endif
