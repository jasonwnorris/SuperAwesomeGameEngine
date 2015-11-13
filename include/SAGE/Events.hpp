// Events.hpp

#ifndef __SAGE_EVENTS_H__
#define __SAGE_EVENTS_H__

// SDL Includes
#include <SDL2/SDL.h>
// SAGE Includes
#include <SAGE/Delegate.hpp>
#include <SAGE/GamePad.hpp>
#include <SAGE/Keyboard.hpp>
#include <SAGE/Mouse.hpp>
// STL Incluides
#include <string>

namespace SAGE
{
	class Events
	{
		public:
			static void Poll();

			static Delegate<void> OnQuit;
			static Delegate<void> OnAppTerminating;
			static Delegate<void> OnAppLowMemory;
			static Delegate<void> OnAppWillEnterBackground;
			static Delegate<void> OnAppDidEnterBackground;
			static Delegate<void> OnAppWillEnterForeground;
			static Delegate<void> OnAppDidEnterForeground;
			static Delegate<void> OnWindowShown;
			static Delegate<void> OnWindowHidden;
			static Delegate<void> OnWindowExposed;
			static Delegate<void, Sint32, Sint32> OnWindowMoved;
			static Delegate<void, Sint32, Sint32> OnWindowResized;
			static Delegate<void> OnWindowMinimized;
			static Delegate<void> OnWindowMaximized;
			static Delegate<void> OnWindowRestored;
			static Delegate<void> OnWindowEnter;
			static Delegate<void> OnWindowLeave;
			static Delegate<void> OnWindowFocusGain;
			static Delegate<void> OnWindowFocusLost;
			static Delegate<void> OnWindowClosed;
			static Delegate<void> OnSysWMEvent;
			static Delegate<void, Key, KeyMod, bool> OnKeyDown;
			static Delegate<void, Key, KeyMod, bool> OnKeyUp;
			static Delegate<void> OnTextEditing;
			static Delegate<void> OnTextInput;
			static Delegate<void, Sint32, Sint32, Sint32, Sint32> OnMouseMotion;
			static Delegate<void, Sint32, Sint32> OnMouseLeftButtonDown;
			static Delegate<void, Sint32, Sint32> OnMouseLeftButtonUp;
			static Delegate<void, Sint32, Sint32> OnMouseRightButtonDown;
			static Delegate<void, Sint32, Sint32> OnMouseRightButtonUp;
			static Delegate<void, Sint32, Sint32> OnMouseMiddleButtonDown;
			static Delegate<void, Sint32, Sint32> OnMouseMiddleButtonUp;
			static Delegate<void, Sint32, Sint32> OnMouseExtra1ButtonDown;
			static Delegate<void, Sint32, Sint32> OnMouseExtra1ButtonUp;
			static Delegate<void, Sint32, Sint32> OnMouseExtra2ButtonDown;
			static Delegate<void, Sint32, Sint32> OnMouseExtra2ButtonUp;
			static Delegate<void, Sint32, Sint32> OnMouseWheel;
			static Delegate<void> OnJoyAxisMotion;
			static Delegate<void> OnJoyBallMotion;
			static Delegate<void> OnJoyHatMotion;
			static Delegate<void> OnJoyBallButtonDown;
			static Delegate<void> OnJoyBallButtonUp;
			static Delegate<void> OnJoyDeviceAdded;
			static Delegate<void> OnJoyDeviceRemoved;
			static Delegate<void, PlayerIndex, GamePadAxis, Sint16> OnControllerAxisMotion;
			static Delegate<void, PlayerIndex, GamePadButton> OnControllerButtonDown;
			static Delegate<void, PlayerIndex, GamePadButton> OnControllerButtonUp;
			static Delegate<void, PlayerIndex> OnControllerDeviceAdded;
			static Delegate<void, PlayerIndex> OnControllerDeviceRemoved;
			static Delegate<void, PlayerIndex> OnControllerDeviceRemapped;
			static Delegate<void> OnFingerDown;
			static Delegate<void> OnFingerUp;
			static Delegate<void> OnFingerMotion;
			static Delegate<void> OnDollarGesture;
			static Delegate<void> OnDollarRecord;
			static Delegate<void> OnMultiGesture;
			static Delegate<void> OnClipboardUpdate;
			static Delegate<void, std::string> OnDropFile;
			static Delegate<void> OnUserEvent;
			static Delegate<void> OnUndefined;

		private:
			Events() = delete;
			~Events() = delete;

			static SDL_Event sEvent;
	};
}

#endif
