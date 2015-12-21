// Mouse.hpp

#ifndef __SAGE_MOUSE_H__
#define __SAGE_MOUSE_H__

// SAGE Includes
#include <SAGE/Events.hpp>
#include <SAGE/Vector2.hpp>

namespace SAGE
{
	enum class MouseButton : int
	{
		Left = SDL_BUTTON_LEFT,
		Middle = SDL_BUTTON_MIDDLE,
		Right = SDL_BUTTON_RIGHT,
		Extra1 = SDL_BUTTON_X1,
		Extra2 = SDL_BUTTON_X2,
	};

	class Mouse
	{
		friend class Events;

		public:
			static void GetPosition(int& p_X, int& p_Y);
			static void GetPosition(Vector2& p_Position);
			static Vector2 GetPosition();
			static void GetMovement(int& p_X, int& p_Y);
			static void GetMovement(Vector2& p_Movement);
			static Vector2 GetMovement();
			static bool IsButtonDown(MouseButton p_Button);
			static bool IsButtonUp(MouseButton p_Button);
			static bool IsButtonClicked(MouseButton p_Button);
			static bool IsButtonReleased(MouseButton p_Button);
			static bool IsScrolledUp();
			static bool IsScrolledDown();

		private:
			Mouse() = delete;
			~Mouse() = delete;

			static void Clear();
			static void SetPosition(int p_X, int p_Y);
			static void SetScroll(int p_X, int p_Y);
			static inline int ButtonMask(MouseButton p_Button);

			static int sPreviousX;
			static int sCurrentX;
			static int sPreviousY;
			static int sCurrentY;
			static Uint32 sPreviousState;
			static Uint32 sCurrentState;
			static bool sScrollUp;
			static bool sScrollDown;
	};
}

#endif
