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
			Surface(Uint32 p_Flags, int p_Width, int p_Height, int p_Depth, Uint32 p_RedMask, Uint32 p_GreenMask, Uint32 p_BlueMask, Uint32 p_AlphaMask);
			Surface(void* p_Pixels, int p_Width, int p_Height, int p_Depth, int p_Pitch, Uint32 p_RedMask, Uint32 p_GreenMask, Uint32 p_BlueMask, Uint32 p_AlphaMask);
			Surface(const std::string& p_Filename);
			~Surface();

			SDL_Surface* GetC() const;

			int SetColorKey(Uint32 p_Key);

		private:
			SDL_Surface* m_Surface;
	};
}

#endif
