// Keyboard.hpp

#ifndef __SAGE_KEYBOARD_H__
#define __SAGE_KEYBOARD_H__

// SDL Includes
#include <SDL2\SDL.h>
// STD Includes
#include <map>

namespace SAGE
{
	enum class Key: Sint32
	{
		Escape = SDLK_ESCAPE,
		Space = SDLK_SPACE,
		Tab = SDLK_TAB,
		Backspace = SDLK_BACKSPACE,
		Delete = SDLK_DELETE,
		Clear = SDLK_CLEAR,
		Return = SDLK_RETURN,
		Pause = SDLK_PAUSE,
		// Symbol Keys
		ExclamationMark = SDLK_EXCLAIM,
		QuestionMark = SDLK_QUESTION,
		SingleQuote = SDLK_QUOTE,
		DoubleQuote = SDLK_QUOTEDBL,
		BackQuote = SDLK_BACKQUOTE,
		At = SDLK_AT,
		Caret = SDLK_CARET,
		Underscore = SDLK_UNDERSCORE,
		Grave = SDLK_BACKQUOTE,
		Hash = SDLK_HASH,
		Percent = SDLK_PERCENT,
		Dollar = SDLK_DOLLAR,
		Ampersand = SDLK_AMPERSAND,
		LeftParenthesis = SDLK_LEFTPAREN,
		RightParenthesis = SDLK_RIGHTPAREN,
		LeftBracket = SDLK_LEFTBRACKET,
		RightBracket = SDLK_RIGHTBRACKET,
		Asterisk = SDLK_ASTERISK,
		Plus = SDLK_PLUS,
		Comma = SDLK_COMMA,
		Minus = SDLK_MINUS,
		Period = SDLK_PERIOD,
		ForwardSlash = SDLK_SLASH,
		BackSlash = SDLK_BACKSLASH,
		// Number Keys
		Number0 = SDLK_0,
		Number1 = SDLK_1,
		Number2 = SDLK_2,
		Number3 = SDLK_3,
		Number4 = SDLK_4,
		Number5 = SDLK_5,
		Number6 = SDLK_6,
		Number7 = SDLK_7,
		Number8 = SDLK_8,
		Number9 = SDLK_9,
		Colon = SDLK_COLON,
		Semicolon = SDLK_SEMICOLON,
		LessThan = SDLK_LESS,
		GreaterThan = SDLK_GREATER,
		Equals = SDLK_EQUALS,
		// Alphabet
		A = SDLK_a,
		B = SDLK_b,
		C = SDLK_c,
		D = SDLK_d,
		E = SDLK_e,
		F = SDLK_f,
		G = SDLK_g,
		H = SDLK_h,
		I = SDLK_i,
		J = SDLK_j,
		K = SDLK_k,
		L = SDLK_l,
		M = SDLK_m,
		N = SDLK_n,
		O = SDLK_o,
		P = SDLK_p,
		Q = SDLK_q,
		R = SDLK_r,
		S = SDLK_s,
		T = SDLK_t,
		U = SDLK_u,
		V = SDLK_v,
		W = SDLK_w,
		X = SDLK_x,
		Y = SDLK_y,
		Z = SDLK_z,
		// Keypad
		Keypad0 = SDLK_KP_0,
		Keypad00 = SDLK_KP_00,
		Keypad000 = SDLK_KP_000,
		Keypad1 = SDLK_KP_1,
		Keypad2 = SDLK_KP_2,
		Keypad3 = SDLK_KP_3,
		Keypad4 = SDLK_KP_4,
		Keypad5 = SDLK_KP_5,
		Keypad6 = SDLK_KP_6,
		Keypad7 = SDLK_KP_7,
		Keypad8 = SDLK_KP_8,
		Keypad9 = SDLK_KP_9,
		KeypadPeriod = SDLK_KP_PERIOD,
		KeypadDivide = SDLK_KP_DIVIDE,
		KeypadMultiply = SDLK_KP_MULTIPLY,
		KeypadMinus = SDLK_KP_MINUS,
		KeypadPlus = SDLK_KP_PLUS,
		KeypadEnter = SDLK_KP_ENTER,
		KeypadEquals = SDLK_KP_EQUALS,
		ThousandsSeparator = SDLK_THOUSANDSSEPARATOR,
		DecimalSeparator = SDLK_DECIMALSEPARATOR,
		CurrencyUnit = SDLK_CURRENCYUNIT,
		CurrencySubUnit = SDLK_CURRENCYSUBUNIT,
		// Directional Keys
		Up = SDLK_UP,
		Down = SDLK_DOWN,
		Left = SDLK_LEFT,
		Right = SDLK_RIGHT,
		// ? Keys
		Insert = SDLK_INSERT,
		Home = SDLK_HOME,
		End = SDLK_END,
		PageUp = SDLK_PAGEUP,
		PageDown = SDLK_PAGEDOWN,
		// Function Keys
		F1 = SDLK_F1,
		F2 = SDLK_F2,
		F3 = SDLK_F3,
		F4 = SDLK_F4,
		F5 = SDLK_F5,
		F6 = SDLK_F6,
		F7 = SDLK_F7,
		F8 = SDLK_F8,
		F9 = SDLK_F9,
		F10 = SDLK_F10,
		F11 = SDLK_F11,
		F12 = SDLK_F12,
		F13 = SDLK_F13,
		F14 = SDLK_F14,
		F15 = SDLK_F15,
		F16 = SDLK_F16,
		F17 = SDLK_F17,
		F18 = SDLK_F18,
		F19 = SDLK_F19,
		F20 = SDLK_F20,
		F21 = SDLK_F21,
		F22 = SDLK_F22,
		F23 = SDLK_F23,
		F24 = SDLK_F24,
		// Lock Keys
		NumLock = SDLK_NUMLOCKCLEAR,
		CapsLock = SDLK_CAPSLOCK,
		ScrollLock = SDLK_SCROLLLOCK,
		// Mod Keys
		RightShift = SDLK_RSHIFT,
		LeftShift = SDLK_LSHIFT,
		RightControl = SDLK_RCTRL,
		LeftControl = SDLK_LCTRL,
		RightAlt = SDLK_RALT,
		LeftAlt = SDLK_LALT,
		RightGUI = SDLK_RGUI,
		LeftGUI = SDLK_LGUI,
		Mode = SDLK_MODE,
		// Audio Keys
		AudioNext = SDLK_AUDIONEXT,
		AudioPrevious = SDLK_AUDIOPREV,
		AudioStop = SDLK_AUDIOSTOP,
		AudioPlay = SDLK_AUDIOPLAY,
		AudioMute = SDLK_AUDIOMUTE,
		MediaSelect = SDLK_MEDIASELECT,
		// Utility Keys
		WWW = SDLK_WWW,
		Mail = SDLK_MAIL,
		Calculator = SDLK_CALCULATOR,
		Computer = SDLK_COMPUTER,
		ACSearch = SDLK_AC_SEARCH,
		ACHome = SDLK_AC_HOME,
		ACBackward = SDLK_AC_BACK,
		ACForward = SDLK_AC_FORWARD,
		ACStop = SDLK_AC_STOP,
		ACRefresh = SDLK_AC_REFRESH,
		ACBookmarks = SDLK_AC_BOOKMARKS,
		// Monitor Keys
		BrightnessDown = SDLK_BRIGHTNESSDOWN,
		BrightnessUp = SDLK_BRIGHTNESSUP,
		DisplaySwitch = SDLK_DISPLAYSWITCH,
		// Keybaord Illumination Keys
		IlluminationToggle = SDLK_KBDILLUMTOGGLE,
		IlluminationDown = SDLK_KBDILLUMDOWN,
		IlluminationUp = SDLK_KBDILLUMUP,
		// System Keys
		Eject = SDLK_EJECT,
		Sleep = SDLK_SLEEP,
		Help = SDLK_HELP,
		PrintScreen = SDLK_PRINTSCREEN,
		SysReq = SDLK_SYSREQ,
		Menu = SDLK_MENU,
		Power = SDLK_POWER,
		Application = SDLK_APPLICATION,
		// Processing Keys
		Again = SDLK_AGAIN,
		Undo = SDLK_UNDO,
		Cut = SDLK_CUT,
		Copy = SDLK_COPY,
		Paste = SDLK_PASTE,
	};
	
	enum class KeyMod : int
	{
		None = KMOD_NONE,
		LeftShift = KMOD_LSHIFT,
		RightShift = KMOD_RSHIFT,
		Shift = LeftShift | RightShift,
		LeftControl = KMOD_LCTRL,
		RightControl = KMOD_RCTRL,
		Control = LeftControl | RightControl,
		LeftAlt = KMOD_LALT,
		RightAlt = KMOD_RALT,
		Alt = LeftAlt | RightAlt,
		LeftGUI = KMOD_LGUI,
		RightGUI = KMOD_RGUI,
		GUI = LeftGUI | RightGUI,
		Num = KMOD_NUM,
		Caps = KMOD_CAPS,
		Mode = KMOD_MODE,
		Reserved = KMOD_RESERVED,
	};

	class Keyboard
	{
		friend class Events;

		public:
			static bool IsKeyDown(Key pKey);
			static bool IsKeyUp(Key pKey);
			static bool IsKeyPressed(Key pKey);
			static bool IsKeyReleased(Key pKey);

		private:
			Keyboard() = delete;
			~Keyboard() = delete;

			static void Clear();
			static void SetKey(Key pKey, bool pState);

			static std::map<Key, bool> sCurrentKeys;
			static std::map<Key, bool> sPreviousKeys;
	};
}

#endif
