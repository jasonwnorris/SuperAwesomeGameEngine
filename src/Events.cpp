// Events.cpp

// SAGE Includes
#include <SAGE/Events.hpp>
#include <SAGE/GamePad.hpp>
#include <SAGE/Keyboard.hpp>
#include <SAGE/Mouse.hpp>

namespace SAGE
{
	Delegate<void> Events::OnQuit;
	Delegate<void> Events::OnAppTerminating;
	Delegate<void> Events::OnAppLowMemory;
	Delegate<void> Events::OnAppWillEnterBackground;
	Delegate<void> Events::OnAppDidEnterBackground;
	Delegate<void> Events::OnAppWillEnterForeground;
	Delegate<void> Events::OnAppDidEnterForeground;
	Delegate<void> Events::OnWindowShown;
	Delegate<void> Events::OnWindowHidden;
	Delegate<void> Events::OnWindowExposed;
	Delegate<void, Sint32, Sint32> Events::OnWindowMoved;
	Delegate<void, Sint32, Sint32> Events::OnWindowResized;
	Delegate<void> Events::OnWindowMinimized;
	Delegate<void> Events::OnWindowMaximized;
	Delegate<void> Events::OnWindowRestored;
	Delegate<void> Events::OnWindowEnter;
	Delegate<void> Events::OnWindowLeave;
	Delegate<void> Events::OnWindowFocusGain;
	Delegate<void> Events::OnWindowFocusLost;
	Delegate<void> Events::OnWindowClosed;
	Delegate<void> Events::OnSysWMEvent;
	Delegate<void, Key, KeyMod, bool> Events::OnKeyDown;
	Delegate<void, Key, KeyMod, bool> Events::OnKeyUp;
	Delegate<void> Events::OnTextEditing;
	Delegate<void> Events::OnTextInput;
	Delegate<void, Sint32, Sint32, Sint32, Sint32> Events::OnMouseMotion;
	Delegate<void, Sint32, Sint32> Events::OnMouseLeftButtonDown;
	Delegate<void, Sint32, Sint32> Events::OnMouseLeftButtonUp;
	Delegate<void, Sint32, Sint32> Events::OnMouseRightButtonDown;
	Delegate<void, Sint32, Sint32> Events::OnMouseRightButtonUp;
	Delegate<void, Sint32, Sint32> Events::OnMouseMiddleButtonDown;
	Delegate<void, Sint32, Sint32> Events::OnMouseMiddleButtonUp;
	Delegate<void, Sint32, Sint32> Events::OnMouseExtra1ButtonDown;
	Delegate<void, Sint32, Sint32> Events::OnMouseExtra1ButtonUp;
	Delegate<void, Sint32, Sint32> Events::OnMouseExtra2ButtonDown;
	Delegate<void, Sint32, Sint32> Events::OnMouseExtra2ButtonUp;
	Delegate<void, Sint32, Sint32> Events::OnMouseWheel;
	Delegate<void> Events::OnJoyAxisMotion;
	Delegate<void> Events::OnJoyBallMotion;
	Delegate<void> Events::OnJoyHatMotion;
	Delegate<void> Events::OnJoyBallButtonDown;
	Delegate<void> Events::OnJoyBallButtonUp;
	Delegate<void> Events::OnJoyDeviceAdded;
	Delegate<void> Events::OnJoyDeviceRemoved;
	Delegate<void, PlayerIndex, GamePadAxis, Sint16> Events::OnControllerAxisMotion;
	Delegate<void, PlayerIndex, GamePadButton> Events::OnControllerButtonDown;
	Delegate<void, PlayerIndex, GamePadButton> Events::OnControllerButtonUp;
	Delegate<void, PlayerIndex> Events::OnControllerDeviceAdded;
	Delegate<void, PlayerIndex> Events::OnControllerDeviceRemoved;
	Delegate<void, PlayerIndex> Events::OnControllerDeviceRemapped;
	Delegate<void> Events::OnFingerDown;
	Delegate<void> Events::OnFingerUp;
	Delegate<void> Events::OnFingerMotion;
	Delegate<void> Events::OnDollarGesture;
	Delegate<void> Events::OnDollarRecord;
	Delegate<void> Events::OnMultiGesture;
	Delegate<void> Events::OnClipboardUpdate;
	Delegate<void, std::string> Events::OnDropFile;
	Delegate<void> Events::OnUserEvent;
	Delegate<void> Events::OnUndefined;

	SDL_Event Events::sEvent;

	void Events::Poll()
	{
		Keyboard::Clear();
		Mouse::Clear();
		GamePad::ClearAll();

		while (SDL_PollEvent(&sEvent))
		{
			switch (sEvent.type)
			{
				case SDL_QUIT:
					OnQuit();
					break;
				case SDL_APP_TERMINATING:
					OnAppTerminating();
					break;
				case SDL_APP_LOWMEMORY:
					OnAppLowMemory();
					break;
				case SDL_APP_WILLENTERBACKGROUND:
					OnAppWillEnterBackground();
					break;
				case SDL_APP_DIDENTERBACKGROUND:
					OnAppDidEnterBackground();
					break;
				case SDL_APP_WILLENTERFOREGROUND:
					OnAppWillEnterForeground();
					break;
				case SDL_APP_DIDENTERFOREGROUND:
					OnAppDidEnterForeground();
					break;
				case SDL_WINDOWEVENT:
					switch (sEvent.window.event)
					{
						case SDL_WINDOWEVENT_SHOWN:
							OnWindowShown();
							break;
						case SDL_WINDOWEVENT_HIDDEN:
							OnWindowHidden();
							break;
						case SDL_WINDOWEVENT_EXPOSED:
							OnWindowExposed();
							break;
						case SDL_WINDOWEVENT_MOVED:
							OnWindowMoved(sEvent.window.data1, sEvent.window.data2);
							break;
						case SDL_WINDOWEVENT_RESIZED:
							OnWindowResized(sEvent.window.data1, sEvent.window.data2);
							break;
						case SDL_WINDOWEVENT_MINIMIZED:
							OnWindowMinimized();
							break;
						case SDL_WINDOWEVENT_MAXIMIZED:
							OnWindowMaximized();
							break;
						case SDL_WINDOWEVENT_RESTORED:
							OnWindowRestored();
							break;
						case SDL_WINDOWEVENT_ENTER:
							OnWindowEnter();
							break;
						case SDL_WINDOWEVENT_LEAVE:
							OnWindowLeave();
							break;
						case SDL_WINDOWEVENT_FOCUS_GAINED:
							OnWindowFocusGain();
							break;
						case SDL_WINDOWEVENT_FOCUS_LOST:
							OnWindowFocusLost();
							break;
						case SDL_WINDOWEVENT_CLOSE:
							OnWindowClosed();
							break;
						default:
							break;
					}
					break;
				case SDL_SYSWMEVENT:
					OnSysWMEvent();
					break;
				case SDL_KEYDOWN:
					OnKeyDown(static_cast<Key>(sEvent.key.keysym.sym), static_cast<KeyMod>(sEvent.key.keysym.mod), sEvent.key.repeat != 0);
					Keyboard::SetKey(static_cast<Key>(sEvent.key.keysym.sym), true);
					break;
				case SDL_KEYUP:
					OnKeyUp(static_cast<Key>(sEvent.key.keysym.sym), static_cast<KeyMod>(sEvent.key.keysym.mod), sEvent.key.repeat != 0);
					Keyboard::SetKey(static_cast<Key>(sEvent.key.keysym.sym), false);
					break;
				case SDL_TEXTEDITING:
					OnTextEditing();
					break;
				case SDL_TEXTINPUT:
					OnTextInput();
					break;
				case SDL_MOUSEMOTION:
					OnMouseMotion(sEvent.motion.x, sEvent.motion.y, sEvent.motion.xrel, sEvent.motion.yrel);
					Mouse::SetPosition(sEvent.motion.x, sEvent.motion.y);
					break;
				case SDL_MOUSEBUTTONDOWN:
					switch (static_cast<MouseButton>(sEvent.button.button))
					{
						case MouseButton::Left:
							OnMouseLeftButtonDown(sEvent.button.x, sEvent.button.y);
							break;
						case MouseButton::Middle:
							OnMouseMiddleButtonDown(sEvent.button.x, sEvent.button.y);
							break;
						case MouseButton::Right:
							OnMouseRightButtonDown(sEvent.button.x, sEvent.button.y);
							break;
						case MouseButton::Extra1:
							OnMouseLeftButtonDown(sEvent.button.x, sEvent.button.y);
							break;
						case MouseButton::Extra2:
							OnMouseLeftButtonDown(sEvent.button.x, sEvent.button.y);
							break;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					switch (static_cast<MouseButton>(sEvent.button.button))
					{
						case MouseButton::Left:
							OnMouseLeftButtonUp(sEvent.button.x, sEvent.button.y);
							break;
						case MouseButton::Middle:
							OnMouseMiddleButtonUp(sEvent.button.x, sEvent.button.y);
							break;
						case MouseButton::Right:
							OnMouseRightButtonUp(sEvent.button.x, sEvent.button.y);
							break;
						case MouseButton::Extra1:
							OnMouseLeftButtonUp(sEvent.button.x, sEvent.button.y);
							break;
						case MouseButton::Extra2:
							OnMouseLeftButtonUp(sEvent.button.x, sEvent.button.y);
							break;
					}
					break;
				case SDL_MOUSEWHEEL:
					OnMouseWheel(sEvent.wheel.x, sEvent.wheel.y);
					Mouse::SetScroll(sEvent.wheel.x, sEvent.wheel.y);
					break;
				case SDL_JOYAXISMOTION:
					OnJoyAxisMotion();
					break;
				case SDL_JOYBALLMOTION:
					OnJoyBallMotion();
					break;
				case SDL_JOYHATMOTION:
					OnJoyHatMotion();
					break;
				case SDL_JOYBUTTONDOWN:
					OnJoyBallButtonDown();
					break;
				case SDL_JOYBUTTONUP:
					OnJoyBallButtonUp();
					break;
				case SDL_JOYDEVICEADDED:
					OnJoyDeviceAdded();
					break;
				case SDL_JOYDEVICEREMOVED:
					OnJoyDeviceRemoved();
					break;
				case SDL_CONTROLLERAXISMOTION:
					OnControllerAxisMotion(static_cast<PlayerIndex>(sEvent.cdevice.which), static_cast<GamePadAxis>(sEvent.caxis.axis), sEvent.caxis.value);
					GamePad::SetAxis(static_cast<PlayerIndex>(sEvent.cdevice.which), static_cast<GamePadAxis>(sEvent.caxis.axis), sEvent.caxis.value);
					break;
				case SDL_CONTROLLERBUTTONDOWN:
					OnControllerButtonDown(static_cast<PlayerIndex>(sEvent.cdevice.which), static_cast<GamePadButton>(sEvent.cbutton.button));
					GamePad::SetButton(static_cast<PlayerIndex>(sEvent.cdevice.which), static_cast<GamePadButton>(sEvent.cbutton.button), true);
					break;
				case SDL_CONTROLLERBUTTONUP:
					OnControllerButtonUp(static_cast<PlayerIndex>(sEvent.cdevice.which), static_cast<GamePadButton>(sEvent.cbutton.button));
					GamePad::SetButton(static_cast<PlayerIndex>(sEvent.cdevice.which), static_cast<GamePadButton>(sEvent.cbutton.button), false);
					break;
				case SDL_CONTROLLERDEVICEADDED:
					OnControllerDeviceAdded(static_cast<PlayerIndex>(sEvent.cdevice.which));
					GamePad::Open(static_cast<PlayerIndex>(sEvent.cdevice.which));
					break;
				case SDL_CONTROLLERDEVICEREMOVED:
					OnControllerDeviceRemoved(static_cast<PlayerIndex>(sEvent.cdevice.which));
					GamePad::Close(static_cast<PlayerIndex>(sEvent.cdevice.which));
					break;
				case SDL_CONTROLLERDEVICEREMAPPED:
					OnControllerDeviceRemapped(static_cast<PlayerIndex>(sEvent.cdevice.which));
					GamePad::Remap(static_cast<PlayerIndex>(sEvent.cdevice.which));
					break;
				case SDL_FINGERDOWN:
					OnFingerDown();
					break;
				case SDL_FINGERUP:
					OnFingerUp();
					break;
				case SDL_FINGERMOTION:
					OnFingerMotion();
					break;
				case SDL_DOLLARGESTURE:
					OnDollarGesture();
					break;
				case SDL_DOLLARRECORD:
					OnDollarRecord();
					break;
				case SDL_MULTIGESTURE:
					OnMultiGesture();
					break;
				case SDL_CLIPBOARDUPDATE:
					OnClipboardUpdate();
					break;
				case SDL_DROPFILE:
					OnDropFile(sEvent.drop.file);
					break;
				case SDL_USEREVENT:
					OnUserEvent();
					break;
				default:
					OnUndefined();
					break;
			}
		}
	}
}
