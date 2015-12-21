// Engine.cpp

// OpenGL Includes
#if defined __ANDROID__
	#include <GLES3/gl3.h>
#else
	#include <GL/glew.h>
#endif
// SDL Includes
#if defined __ANDROID__
	#include <SDL_image.h>
	#include <SDL_ttf.h>
	#include <SDL_mixer.h>
	#include <SDL_net.h>
#else
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_ttf.h>
	#include <SDL2/SDL_mixer.h>
	#include <SDL2/SDL_net.h>
#endif
// SAGE Includes
#include <SAGE/Engine.hpp>

namespace SAGE
{
	Engine::Engine()
	{
		m_IsInitialized = false;
	}

	Engine::~Engine()
	{
		if (m_IsInitialized)
		{
			Finalize();
		}
	}

	bool Engine::Initialize()
	{
		// Initialize SDL.
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			SDL_Log("[Window::Initialize] Failed to initialize SDL: %s", SDL_GetError());
			return false;
		}

		// Initialize SDL_image.
		int imgFlags = IMG_INIT_PNG;
		if ((IMG_Init(imgFlags) & imgFlags) != imgFlags)
		{
			SDL_Log("Failed to initialize SDL_image: %s", SDL_GetError());
			return false;
		}

		// Initialize SDL_ttf.
		if (TTF_Init() < 0)
		{
			SDL_Log("Failed to initialize SDL_ttf: %s", SDL_GetError());
			return false;
		}

		// Initialize SDL_mixer.
		int mixFlags = 0;
		if ((Mix_Init(mixFlags) & mixFlags) != mixFlags)
		{
			SDL_Log("Failed to initialize SDL_mixer: %s", SDL_GetError());
			return false;
		}

		// Initialize audio device.
		int frequency = 44100;
		int format = AUDIO_S16LSB;
		int channels = 2;
		int chunksize = 1024;
		if (Mix_OpenAudio(frequency, format, channels, chunksize) < 0)
		{
			SDL_Log("Failed to initialize audio device: %s", SDL_GetError());
			return false;
		}

		// Initialize SDL_net.
		if (SDLNet_Init() < 0)
		{
			SDL_Log("Failed to initialize SDL_net: %s", SDL_GetError());
			return false;
		}
		
		// Set OpenGL values.
		if (SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8) < 0)
		{
			SDL_Log("[Window::Initialize] Failed to set red size: %s", SDL_GetError());
			return false;
		}
		if (SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8) < 0)
		{
			SDL_Log("[Window::Initialize] Failed to set green size: %s", SDL_GetError());
			return false;
		}
		if (SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8) < 0)
		{
			SDL_Log("[Window::Initialize] Failed to set blue size: %s", SDL_GetError());
			return false;
		}
		if (SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8) < 0)
		{
			SDL_Log("[Window::Initialize] Failed to set alpha size: %s", SDL_GetError());
			return false;
		}
		if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) < 0)
		{
			SDL_Log("[Window::Initialize] Failed to set doublebuffer: %s", SDL_GetError());
			return false;
		}

		// Set OpenGL context profile.
#if defined _WIN32
		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY) < 0)
#elif defined __ANDROID__
		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES) < 0)
#else
		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) < 0)
#endif
		{
			SDL_Log("Failed to set context profile mask: %s", SDL_GetError());
			return false;
		}

		// Set OpenGL major version.
#if defined _WIN32
		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4) < 0)
#else
		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) < 0)
#endif
		{
			SDL_Log("Failed to set context major version: %s", SDL_GetError());
			return false;
		}

		// Set OpenGL minor version.
#if defined _WIN32
		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3) < 0)
#elif defined __ANDROID__
		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0) < 0)
#else
		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2) < 0)
#endif
		{
			SDL_Log("Failed to set context minor version: %s", SDL_GetError());
			return false;
		}

#if !defined __ANDROID__
		// Create temporary window and context to enable GLew. 	
		SDL_Window* window = SDL_CreateWindow("", 0, 0, 0, 0, 0);
		SDL_GLContext context = SDL_GL_CreateContext(window);
		SDL_GL_MakeCurrent(window, context);

		// Enable GLew.
		glewExperimental = GL_TRUE;
		GLenum result = glewInit();
		if (result != GLEW_OK)
		{
			SDL_Log("Failed to initialize GLew: %s", glewGetErrorString(result));
			return false;
		}
#endif

		// Print OpenGL information.
		SDL_Log("OpenGL Version: %s", glGetString(GL_VERSION));
		SDL_Log("GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
		SDL_Log("Vendor: %s", glGetString(GL_VENDOR));
		SDL_Log("Renderer: %s", glGetString(GL_RENDERER));

#if !defined __ANDROID__
		// Destroy temporary window and context.		
		SDL_GL_MakeCurrent(window, nullptr);
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(window);
#endif

		return (m_IsInitialized = true);
	}

	bool Engine::Finalize()
	{
		if (!m_IsInitialized)
		{
			SDL_Log("[Engine::Finalize] Engine already finalized. Doing nothing.");
		}
		else
		{
			// Clean up.
			SDLNet_Quit();
			Mix_CloseAudio();
			Mix_Quit();
			TTF_Quit();
			IMG_Quit();
			SDL_Quit();

			m_IsInitialized = false;
		}
		
		return true;
	}
}
