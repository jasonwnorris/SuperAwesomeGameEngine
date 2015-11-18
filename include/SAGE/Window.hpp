// Window.hpp

#ifndef __SAGE_WINDOW_HPP__
#define __SAGE_WINDOW_HPP__

// SAGE Includes
#include <SAGE/Color.hpp>
#include <SAGE/Surface.hpp>
// STL Includes
#include <string>

namespace SAGE
{
	enum MessageBoxLevel
	{
		Information = SDL_MESSAGEBOX_INFORMATION,
		Warning = SDL_MESSAGEBOX_WARNING,
		Error = SDL_MESSAGEBOX_ERROR
	};

	enum MessageBoxButton
	{
		Abort,
		Cancel,
		Ignore,
		No,
		OK,
		Retry,
		Yes
	};

	enum MessageBoxButtonSet
	{
		AbortRetryIgnoreSet,
		OKSet,
		OKCancelSet,
		RetryCancelSet,
		YesNoSet,
		YesNoCancelSet
	};

	struct MessageBoxScheme
	{
		Color BackgroundColor;
		Color TextColor;
		Color ButtonBorderColor;
		Color ButtonBackgroundColor;
		Color ButtonSelectedColor;

		MessageBoxScheme()
		{
			BackgroundColor = Color::Gray;
			TextColor = Color::Black;
			ButtonBorderColor = Color::Black;
			ButtonBackgroundColor = Color::Gray;
			ButtonSelectedColor = Color::LightGray;
		}
	};

	struct MessageBoxDetails
	{
		MessageBoxLevel Level;
		MessageBoxButtonSet ButtonSet;
		MessageBoxScheme Scheme;

		static const MessageBoxDetails DefaultDetails;

		MessageBoxDetails()
		{
			Level = MessageBoxLevel::Information;
			ButtonSet = MessageBoxButtonSet::OKSet;
		}
	};

	enum WindowMode
	{
		Windowed = SDL_WINDOW_SHOWN,
		BorderlessWindowed = SDL_WINDOW_BORDERLESS,
		Fullscreen = SDL_WINDOW_FULLSCREEN,
		FullscreenWindowed = SDL_WINDOW_FULLSCREEN_DESKTOP,
	};

	struct WindowOptions
	{
		static const std::string DefaultTitle;
		static const int DefaultWidth;
		static const int DefaultHeight;
		static const WindowMode DefaultMode;
		static const bool DefaultVerticalSync;
		static const bool DefaultHidden;

		static const WindowOptions DefaultOptions;

		static bool LoadFromFile(const std::string& p_Filename, WindowOptions& p_WindowOptions);
		static bool SaveToFile(const std::string& p_Filename, const WindowOptions& p_WindowOptions);

		std::string Title;
		int Width;
		int Height;
		WindowMode Mode;
		bool VerticalSync;
		bool Hidden;

		WindowOptions()
		{
			Title = DefaultTitle;
			Width = DefaultWidth;
			Height = DefaultHeight;
			Mode = DefaultMode;
			VerticalSync = DefaultVerticalSync;
			Hidden = DefaultHidden;
		}
	};

	class Window
	{
		public:
			Window();
			~Window();

			SDL_Window* GetC() const;

			bool Initialize(const WindowOptions& p_Options = WindowOptions::DefaultOptions);
			bool Reinitialize(const WindowOptions& p_Options = WindowOptions::DefaultOptions);
			bool Finalize();
			void SetTitle(const std::string& p_Title);
			void SetIcon(const Surface& p_Surface);
			void SetClearColor(const Color& p_Color);
			void Resize(int p_Width, int p_Height);
			bool SetVerticalSync(bool p_Enabled);
			void Show();
			void Hide();
			void Focus();
			void Restore();
			void Maximize();
			void Minimize();
			void Clear();
			void Flip();
			void ShowSimpleMessageBox(const std::string& p_Title, const std::string& p_Text, MessageBoxLevel p_Level = MessageBoxLevel::Information);
			MessageBoxButton ShowCustomMessageBox(const std::string& p_Title, const std::string& p_Text, MessageBoxDetails p_Details = MessageBoxDetails::DefaultDetails);
			void PrintInfo();

		private:
			SDL_Window* m_Window;
			SDL_GLContext m_Context;
			bool m_IsInitialized;
	};
}

#endif
