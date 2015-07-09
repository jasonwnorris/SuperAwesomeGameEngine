// Window.cpp

// GL Includes
#include <gl\glew.h>
// SAGE Includes
#include <SAGE\Window.hpp>
// JsonCpp Includes
#include <json\json.h>
// STL Includes
#include <fstream>

namespace SAGE
{
	const std::string WindowOptions::DefaultTitle = "Untitled Window";
	const int WindowOptions::DefaultWidth = 1024;
	const int WindowOptions::DefaultHeight = 768;
	const WindowMode WindowOptions::DefaultMode = WindowMode::Windowed;
	const bool WindowOptions::DefaultVerticalSync = true;
	const bool WindowOptions::DefaultHidden = false;

	const WindowOptions WindowOptions::DefaultOptions;

	bool WindowOptions::LoadFromFile(const std::string& pFilename, WindowOptions& pWindowOptions)
	{
		// Check for .json extension.
		if (pFilename.substr(pFilename.find_last_of('.') + 1) != "json")
		{
			SDL_Log("[WindowOptions::LoadFromFile] Filename does not have a JSON extension.");

			return false;
		}

		// Open the file.
		std::ifstream file(pFilename, std::ofstream::in);
		if (!file.is_open())
		{
			return false;
		}

		// Parse the JSON document.
		Json::Value root;
		Json::Reader reader;
		bool isParsed = reader.parse(file, root, false);
		if (isParsed)
		{
			// Grab and assign attributes.
			pWindowOptions.Title = root.get("title", DefaultTitle).asString();
			pWindowOptions.Width = root.get("width", DefaultWidth).asInt();
			pWindowOptions.Height = root.get("height", DefaultHeight).asInt();
			pWindowOptions.Mode = static_cast<WindowMode>(root.get("mode", DefaultMode).asInt());
			pWindowOptions.VerticalSync = root.get("vsync", DefaultVerticalSync).asBool();
			pWindowOptions.Hidden = root.get("hidden", DefaultHidden).asBool();
		}
		else
		{
			SDL_Log("[WindowOptions::LoadFromFile] Failed to read JSON file.");
		}

		// Close the file.
		file.close();

		return isParsed;
	}

	bool WindowOptions::SaveToFile(const std::string& pFilename, const WindowOptions& pWindowOptions)
	{
		// Check for .json extension.
		if (pFilename.substr(pFilename.find_last_of('.') + 1) != "json")
		{
			SDL_Log("[WindowOptions::SaveToFile] Filename does not have a JSON extension.");

			return false;
		}

		// Open the file.
		std::ofstream file(pFilename, std::ofstream::out | std::ofstream::trunc);
		if (!file.is_open())
		{
			return false;
		}

		// Construct the JSON.
		Json::Value root;
		root["title"] = pWindowOptions.Title;
		root["width"] = pWindowOptions.Width;
		root["height"] = pWindowOptions.Height;
		root["mode"] = static_cast<int>(pWindowOptions.Mode);
		root["vsync"] = pWindowOptions.VerticalSync;
		root["hidden"] = pWindowOptions.Hidden;

		// Write to the file.
		Json::StyledWriter writer;
		file << writer.write(root);

		// Close the file.
		file.close();

		return true;
	}

	Window::Window()
	{
		mWindow = nullptr;
		mContext = nullptr;
		mIsInitialized = false;
	}

	Window::~Window()
	{
		// Delete the context.
		if (mContext != nullptr)
		{
			SDL_GL_DeleteContext(mContext);
		}

		// Destroy the window.
		if (mWindow != nullptr)
		{
			SDL_DestroyWindow(mWindow);
		}

		// Quit SDL.
		SDL_Quit();
	}

	SDL_Window* Window::GetC() const
	{
		// Return C structure.
		return mWindow;
	}

	bool Window::Initialize(const WindowOptions& pOptions)
	{
		if (mIsInitialized)
		{
			SDL_Log("[Window::Initialize] Window already initialized.");
			return false;
		}

		// Initialize SDL.
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			return false;
		
		// Set OpenGL values.
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		
		// Set OpenGL version.
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		
		// Setup window flags.
		Uint32 flags = SDL_WINDOW_OPENGL;
		if (pOptions.Hidden)
			flags |= SDL_WINDOW_HIDDEN;
		if (pOptions.Mode == WindowMode::Windowed)
			flags |= SDL_WINDOW_SHOWN;
		else if (pOptions.Mode == WindowMode::BorderlessWindowed)
			flags |= SDL_WINDOW_BORDERLESS;
		else if (pOptions.Mode == WindowMode::Fullscreen)
			flags |= SDL_WINDOW_FULLSCREEN;
		else if (pOptions.Mode == WindowMode::FullscreenWindowed)
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		// Create the window.
		mWindow = SDL_CreateWindow(pOptions.Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, pOptions.Width, pOptions.Height, flags);
		if (mWindow == nullptr)
		{
			SDL_Log("[Window::Initialize] Failed to initialize window: %s", SDL_GetError());
			return false;
		}

		// Create the context and make it current to the window.
		mContext = SDL_GL_CreateContext(mWindow);
		if (mContext == nullptr)
		{
			SDL_Log("[Window::Initialize] Failed to create OpenGL context: %s", SDL_GetError());
			return false;
		}
		SDL_GL_MakeCurrent(mWindow, mContext);

		// Configure vertical sync.
		if (!SetVerticalSync(pOptions.VerticalSync))
		{
			return false;
		}

		mIsInitialized = true;

		return true;
	}

	bool Window::Reinitialize(const WindowOptions& pOptions)
	{
		if (!mIsInitialized)
		{
			SDL_Log("[Window::Reinitialize] Window has yet to be initialized.");
			return false;
		}

		// Set title and resize.
		SetTitle(pOptions.Title);
		Resize(pOptions.Width, pOptions.Height);

		// Adjust mode.
		SDL_SetWindowBordered(mWindow, pOptions.Mode == WindowMode::Windowed ? SDL_TRUE : SDL_FALSE);
		if (SDL_SetWindowFullscreen(mWindow, pOptions.Mode == WindowMode::Fullscreen || pOptions.Mode == WindowMode::FullscreenWindowed ? pOptions.Mode : 0) < 0)
		{
			SDL_Log("[Window::Reinitialize] Failed to adjust fullscreen: %s", SDL_GetError());
			return false;
		}

		// Adjust vertical sync.
		if (!SetVerticalSync(pOptions.VerticalSync))
		{
			return false;
		}

		// Check if hidden.
		if (pOptions.Hidden)
			Hide();

		return true;
	}

	bool Window::Finalize()
	{
		if (!mIsInitialized)
		{
			SDL_Log("[Window::Finalize] Window hasn't even been initialized.");
			return false;
		}

		SDL_GL_DeleteContext(mContext);
		SDL_DestroyWindow(mWindow);
		SDL_Quit();

		mIsInitialized = false;

		return true;
	}

	void Window::SetTitle(const std::string& pTitle)
	{
		SDL_SetWindowTitle(mWindow, pTitle.c_str());
	}

	void Window::SetIcon(const Surface& pSurface)
	{
		SDL_SetWindowIcon(mWindow, pSurface.GetC());
	}

	void Window::SetClearColor(const Color& pColor)
	{
		glClearColor(pColor.GetRed(), pColor.GetGreen(), pColor.GetBlue(), pColor.GetAlpha());
	}

	bool Window::SetVerticalSync(bool pEnabled)
	{
		//  0 = immediate
		//  1 = synchronized
		// -1 = late swap tearing (not supporting)
		if (SDL_GL_SetSwapInterval(pEnabled ? 1 : 0) < 0)
			return false;

		return true;
	}

	void Window::Resize(int pWidth, int pHeight)
	{
		SDL_SetWindowSize(mWindow, pWidth, pHeight);
		glViewport(0, 0, pWidth, pHeight);
	}

	void Window::Show()
	{
		SDL_ShowWindow(mWindow);
	}

	void Window::Hide()
	{
		SDL_HideWindow(mWindow);
	}

	void Window::Focus()
	{
		SDL_RaiseWindow(mWindow);
	}

	void Window::Restore()
	{
		SDL_RestoreWindow(mWindow);
	}

	void Window::Maximize()
	{
		SDL_MaximizeWindow(mWindow);
	}

	void Window::Minimize()
	{
		SDL_MinimizeWindow(mWindow);
	}

	void Window::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::Flip()
	{
		SDL_GL_SwapWindow(mWindow);
	}

	void Window::PrintInfo()
	{
		SDL_Log("[Window::PrintInfo] OpenGL Version: %s", glGetString(GL_VERSION));
		SDL_Log("[Window::PrintInfo] GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
		SDL_Log("[Window::PrintInfo] Vendor: %s", glGetString(GL_VENDOR));
		SDL_Log("[Window::PrintInfo] Renderer: %s", glGetString(GL_RENDERER));
	}
}
