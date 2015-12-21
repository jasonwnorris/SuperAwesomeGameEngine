// Window.cpp

// OpenGL Includes
#if defined __ANDROID__
	#include <GLES3/gl3.h>
#else
	#include <GL/glew.h>
#endif
// SAGE Includes
#include <SAGE/Window.hpp>
// JsonCpp Includes
#include <json/json.h>
// STL Includes
#include <fstream>

namespace SAGE
{
	const MessageBoxDetails MessageBoxDetails::DefaultDetails;

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

	Window::Window(Game* p_Game) : IGameComponent(p_Game)
	{
		m_Window = nullptr;
		m_Context = nullptr;
		m_IsInitialized = false;
	}

	Window::~Window()
	{
		if (m_IsInitialized)
		{
			Finalize();
		}
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
		
		// Setup window flags.
#if defined __ANDROID__
		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
		// Grab screen display.
		SDL_DisplayMode display;
		SDL_GetDesktopDisplayMode(0, &display);
		p_Options.Width = display.w;
		p_Options.Height = display.h;
#else
		Uint32 flags = SDL_WINDOW_OPENGL;
		if (p_Options.Hidden)
		{
			flags |= SDL_WINDOW_HIDDEN;
		}
		switch (p_Options.Mode)
		{
			case WindowMode::Windowed:
				flags |= SDL_WINDOW_SHOWN;
				break;
			case WindowMode::BorderlessWindowed:
				flags |= SDL_WINDOW_BORDERLESS;
				break;
			case WindowMode::Fullscreen:
				flags |= SDL_WINDOW_FULLSCREEN;
				break;
			case WindowMode::FullscreenWindowed:
				flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
				break;
		}
#endif

		// Set viewport.
		glViewport(0, 0, p_Options.Width, p_Options.Height);

		// Create the window.
		m_Window = SDL_CreateWindow(p_Options.Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, p_Options.Width, p_Options.Height, flags);
		if (m_Window == nullptr)
		{
			SDL_Log("[Window::Initialize] Failed to create window: %s", SDL_GetError());
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

		// Set OpenGL properties.
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return (m_IsInitialized = true);
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
		SetSize(p_Options.Width, p_Options.Height);

		// Adjust mode.
		Uint32 flags = 0;
		if (p_Options.Mode == WindowMode::Fullscreen || p_Options.Mode == WindowMode::FullscreenWindowed)
		{
			flags = p_Options.Mode;
		}
		SDL_SetWindowBordered(m_Window, p_Options.Mode == WindowMode::Windowed ? SDL_TRUE : SDL_FALSE);
		if (SDL_SetWindowFullscreen(m_Window, flags) < 0)
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
		{
			Hide();
		}

		return true;
	}

	bool Window::Finalize()
	{
		if (!m_IsInitialized)
		{
			SDL_Log("[Window::Finalize] Window already finalized. Doing nothing.");
		}
		else
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

			m_IsInitialized = false;
		}

		return true;
	}

	void Window::GetTitle(std::string& p_Title)
	{
		p_Title = SDL_GetWindowTitle(m_Window);
	}

	void Window::GetPosition(int& p_X, int& p_Y)
	{
		SDL_GetWindowPosition(m_Window, &p_X, &p_Y);
	}

	void Window::GetSize(int& p_Width, int& p_Height)
	{
		SDL_GetWindowSize(m_Window, &p_Width, &p_Height);
	}

	void Window::SetTitle(const std::string& p_Title)
	{
		SDL_SetWindowTitle(m_Window, p_Title.c_str());
	}

	void Window::SetPosition(int p_X, int p_Y)
	{
		SDL_SetWindowPosition(m_Window, p_X, p_Y);
	}

	void Window::SetSize(int p_Width, int p_Height)
	{
		SDL_SetWindowSize(m_Window, p_Width, p_Height);
		glViewport(0, 0, p_Width, p_Height);
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
		{
			SDL_Log("[Window::SetVerticalSync] Error setting vertical sync: %s", SDL_GetError());
			return false;
		}

		return true;
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

	void Window::ShowSimpleMessageBox(const std::string& p_Title, const std::string& p_Text, MessageBoxLevel p_Level)
	{
		if (SDL_ShowSimpleMessageBox(p_Level, p_Title.c_str(), p_Text.c_str(), m_Window) < 0)
		{
			SDL_Log("[Window::ShowSimpleMessageBox] Error showing message box: %s", SDL_GetError());
		}
	}

	MessageBoxButton Window::ShowCustomMessageBox(const std::string& p_Title, const std::string& p_Text, MessageBoxDetails p_Details)
	{
		int buttonCount = 0;
		SDL_MessageBoxButtonData* buttons = nullptr;

		switch (p_Details.ButtonSet)
		{
			case AbortRetryIgnoreSet:
				buttonCount = 3;
				buttons = new SDL_MessageBoxButtonData[buttonCount] {
					{                                       0, MessageBoxButton::Abort,  "Abort" },
					{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, MessageBoxButton::Retry,  "Retry" },
					{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, MessageBoxButton::Ignore, "Ignore" }
				};
				break;
			case OKSet:
				buttonCount = 1;
				buttons = new SDL_MessageBoxButtonData[buttonCount] {
					{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, MessageBoxButton::OK, "OK" }
				};
				break;
			case OKCancelSet:
				buttonCount = 2;
				buttons = new SDL_MessageBoxButtonData[buttonCount] {
					{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, MessageBoxButton::OK,     "OK" },
					{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, MessageBoxButton::Cancel, "Cancel" }
				};
				break;
			case RetryCancelSet:
				buttonCount = 2;
				buttons = new SDL_MessageBoxButtonData[buttonCount] {
					{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, MessageBoxButton::Retry,  "Retry" },
					{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, MessageBoxButton::Cancel,  "Cancel" }
				};
				break;
			case YesNoSet:
				buttonCount = 2;
				buttons = new SDL_MessageBoxButtonData[buttonCount] {
					{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, MessageBoxButton::Yes, "Yes" },
					{                                       0, MessageBoxButton::No,  "No" }
				};
				break;
			case YesNoCancelSet:
				buttonCount = 3;
				buttons = new SDL_MessageBoxButtonData[buttonCount] {
					{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, MessageBoxButton::Yes,    "Yes" },
					{                                       0, MessageBoxButton::No,     "No" },
					{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, MessageBoxButton::Cancel, "Cancel" }
				};
				break;
		}

		const SDL_MessageBoxColorScheme scheme = {
			{
				{
					p_Details.Scheme.BackgroundColor.GetRedAsByte(),
					p_Details.Scheme.BackgroundColor.GetGreenAsByte(),
					p_Details.Scheme.BackgroundColor.GetBlueAsByte()
				},
				{
					p_Details.Scheme.TextColor.GetRedAsByte(),
					p_Details.Scheme.TextColor.GetGreenAsByte(),
					p_Details.Scheme.TextColor.GetBlueAsByte()
				},
				{
					p_Details.Scheme.ButtonBorderColor.GetRedAsByte(),
					p_Details.Scheme.ButtonBorderColor.GetGreenAsByte(),
					p_Details.Scheme.ButtonBorderColor.GetBlueAsByte()
				},
				{
					p_Details.Scheme.ButtonBackgroundColor.GetRedAsByte(),
					p_Details.Scheme.ButtonBackgroundColor.GetGreenAsByte(),
					p_Details.Scheme.ButtonBackgroundColor.GetBlueAsByte()
				},
				{
					p_Details.Scheme.ButtonSelectedColor.GetRedAsByte(),
					p_Details.Scheme.ButtonSelectedColor.GetGreenAsByte(),
					p_Details.Scheme.ButtonSelectedColor.GetBlueAsByte()
				}
			}
		};

		const SDL_MessageBoxData data = {
			static_cast<Uint32>(p_Details.Level),
			m_Window,
			p_Title.c_str(),
			p_Text.c_str(),
			buttonCount,
			buttons,
			&scheme
		};

		int retval;
		if (SDL_ShowMessageBox(&data, &retval) < 0)
		{
			SDL_Log("[Window::ShowCustomMessageBox] Error showing message box: %s", SDL_GetError());
		}

		delete [] buttons;

		return static_cast<MessageBoxButton>(retval);
	}

	void Window::PrintInfo()
	{
		SDL_Log("[Window::PrintInfo] OpenGL Version: %s", glGetString(GL_VERSION));
		SDL_Log("[Window::PrintInfo] GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
		SDL_Log("[Window::PrintInfo] Vendor: %s", glGetString(GL_VENDOR));
		SDL_Log("[Window::PrintInfo] Renderer: %s", glGetString(GL_RENDERER));
	}
}
