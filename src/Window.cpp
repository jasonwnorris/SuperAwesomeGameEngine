// Window.cpp

// GL Includes
#include <GL/glew.h>
// SAGE Includes
#include <SAGE/Window.hpp>
// JsonCpp Includes
#include <json/json.h>
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

	bool WindowOptions::LoadFromFile(const std::string& p_Filename, WindowOptions& p_WindowOptions)
	{
		// Check for .json extension.
		if (p_Filename.substr(p_Filename.find_last_of('.') + 1) != "json")
		{
			SDL_Log("[WindowOptions::LoadFromFile] Filename does not have a JSON extension.");

			return false;
		}

		// Open the file.
		std::ifstream file(p_Filename, std::ofstream::in);
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
			p_WindowOptions.Title = root.get("title", DefaultTitle).asString();
			p_WindowOptions.Width = root.get("width", DefaultWidth).asInt();
			p_WindowOptions.Height = root.get("height", DefaultHeight).asInt();
			p_WindowOptions.Mode = static_cast<WindowMode>(root.get("mode", DefaultMode).asInt());
			p_WindowOptions.VerticalSync = root.get("vsync", DefaultVerticalSync).asBool();
			p_WindowOptions.Hidden = root.get("hidden", DefaultHidden).asBool();
		}
		else
		{
			SDL_Log("[WindowOptions::LoadFromFile] Failed to read JSON file.");
		}

		// Close the file.
		file.close();

		return isParsed;
	}

	bool WindowOptions::SaveToFile(const std::string& p_Filename, const WindowOptions& p_WindowOptions)
	{
		// Check for .json extension.
		if (p_Filename.substr(p_Filename.find_last_of('.') + 1) != "json")
		{
			SDL_Log("[WindowOptions::SaveToFile] Filename does not have a JSON extension.");

			return false;
		}

		// Open the file.
		std::ofstream file(p_Filename, std::ofstream::out | std::ofstream::trunc);
		if (!file.is_open())
		{
			return false;
		}

		// Construct the JSON.
		Json::Value root;
		root["title"] = p_WindowOptions.Title;
		root["width"] = p_WindowOptions.Width;
		root["height"] = p_WindowOptions.Height;
		root["mode"] = static_cast<int>(p_WindowOptions.Mode);
		root["vsync"] = p_WindowOptions.VerticalSync;
		root["hidden"] = p_WindowOptions.Hidden;

		// Write to the file.
		Json::StyledWriter writer;
		file << writer.write(root);

		// Close the file.
		file.close();

		return true;
	}

	Window::Window()
	{
		m_Window = nullptr;
		m_Context = nullptr;
		m_IsInitialized = false;
	}

	Window::~Window()
	{
		// Delete the context.
		if (m_Context != nullptr)
		{
			SDL_GL_DeleteContext(m_Context);
		}

		// Destroy the window.
		if (m_Window != nullptr)
		{
			SDL_DestroyWindow(m_Window);
		}

		// Quit SDL.
		SDL_Quit();
	}

	SDL_Window* Window::GetC() const
	{
		// Return C structure.
		return m_Window;
	}

	bool Window::Initialize(const WindowOptions& p_Options)
	{
		if (m_IsInitialized)
		{
			SDL_Log("[Window::Initialize] Window already initialized. Use Reinitialize to make changes to an existing Window.");
			return false;
		}

		// Initialize SDL.
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			SDL_Log("[Window::Initialize] Failed to initialize SDL: %s", SDL_GetError());
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
		}

		// Set OpenGL major version.
#if defined __ANDROID__
		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) < 0)
#else
		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4) < 0)
#endif
		{
			SDL_Log("Failed to set context major version: %s", SDL_GetError());
		}

		// Set OpenGL minor version.
#if defined __ANDROID__
		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0) < 0)
#else
		if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3) < 0)
#endif
		{
			SDL_Log("Failed to set context minor version: %s", SDL_GetError());
		}
		
		// Setup window flags.
		Uint32 flags = SDL_WINDOW_OPENGL;
		if (p_Options.Hidden)
			flags |= SDL_WINDOW_HIDDEN;
		if (p_Options.Mode == WindowMode::Windowed)
			flags |= SDL_WINDOW_SHOWN;
		else if (p_Options.Mode == WindowMode::BorderlessWindowed)
			flags |= SDL_WINDOW_BORDERLESS;
		else if (p_Options.Mode == WindowMode::Fullscreen)
			flags |= SDL_WINDOW_FULLSCREEN;
		else if (p_Options.Mode == WindowMode::FullscreenWindowed)
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		// Create the window.
		m_Window = SDL_CreateWindow(p_Options.Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, p_Options.Width, p_Options.Height, flags);
		if (m_Window == nullptr)
		{
			SDL_Log("[Window::Initialize] Failed to initialize window: %s", SDL_GetError());
			return false;
		}

		// Create the context and make it current to the window.
		m_Context = SDL_GL_CreateContext(m_Window);
		if (m_Context == nullptr)
		{
			SDL_Log("[Window::Initialize] Failed to create OpenGL context: %s", SDL_GetError());
			return false;
		}
		SDL_GL_MakeCurrent(m_Window, m_Context);

		// Configure vertical sync.
		if (!SetVerticalSync(p_Options.VerticalSync))
		{
			return false;
		}

		m_IsInitialized = true;

		return true;
	}

	bool Window::Reinitialize(const WindowOptions& p_Options)
	{
		if (!m_IsInitialized)
		{
			SDL_Log("[Window::Reinitialize] Window has yet to be initialized.");
			return false;
		}

		// Set title and resize.
		SetTitle(p_Options.Title);
		Resize(p_Options.Width, p_Options.Height);

		// Adjust mode.
		SDL_SetWindowBordered(m_Window, p_Options.Mode == WindowMode::Windowed ? SDL_TRUE : SDL_FALSE);
		if (SDL_SetWindowFullscreen(m_Window, p_Options.Mode == WindowMode::Fullscreen || p_Options.Mode == WindowMode::FullscreenWindowed ? p_Options.Mode : 0) < 0)
		{
			SDL_Log("[Window::Reinitialize] Failed to adjust fullscreen: %s", SDL_GetError());
			return false;
		}

		// Adjust vertical sync.
		if (!SetVerticalSync(p_Options.VerticalSync))
		{
			return false;
		}

		// Check if hidden.
		if (p_Options.Hidden)
			Hide();

		return true;
	}

	bool Window::Finalize()
	{
		if (!m_IsInitialized)
		{
			SDL_Log("[Window::Finalize] Window hasn't even been initialized.");
			return false;
		}

		SDL_GL_DeleteContext(m_Context);
		SDL_DestroyWindow(m_Window);
		SDL_Quit();

		m_IsInitialized = false;

		return true;
	}

	void Window::SetTitle(const std::string& p_Title)
	{
		SDL_SetWindowTitle(m_Window, p_Title.c_str());
	}

	void Window::SetIcon(const Surface& p_Surface)
	{
		SDL_SetWindowIcon(m_Window, p_Surface.GetC());
	}

	void Window::SetClearColor(const Color& p_Color)
	{
		glClearColor(p_Color.GetRed(), p_Color.GetGreen(), p_Color.GetBlue(), p_Color.GetAlpha());
	}

	bool Window::SetVerticalSync(bool p_Enabled)
	{
		//  0 = immediate
		//  1 = synchronized
		// -1 = late swap tearing (not supporting)
		if (SDL_GL_SetSwapInterval(p_Enabled ? 1 : 0) < 0)
			return false;

		return true;
	}

	void Window::Resize(int p_Width, int p_Height)
	{
		SDL_SetWindowSize(m_Window, p_Width, p_Height);
		glViewport(0, 0, p_Width, p_Height);
	}

	void Window::Show()
	{
		SDL_ShowWindow(m_Window);
	}

	void Window::Hide()
	{
		SDL_HideWindow(m_Window);
	}

	void Window::Focus()
	{
		SDL_RaiseWindow(m_Window);
	}

	void Window::Restore()
	{
		SDL_RestoreWindow(m_Window);
	}

	void Window::Maximize()
	{
		SDL_MaximizeWindow(m_Window);
	}

	void Window::Minimize()
	{
		SDL_MinimizeWindow(m_Window);
	}

	void Window::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::Flip()
	{
		SDL_GL_SwapWindow(m_Window);
	}

	void Window::PrintInfo()
	{
		SDL_Log("[Window::PrintInfo] OpenGL Version: %s", glGetString(GL_VERSION));
		SDL_Log("[Window::PrintInfo] GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
		SDL_Log("[Window::PrintInfo] Vendor: %s", glGetString(GL_VENDOR));
		SDL_Log("[Window::PrintInfo] Renderer: %s", glGetString(GL_RENDERER));
	}
}
