// Mouse.hpp

#ifndef __SAGE_MOUSE_H__
#define __SAGE_MOUSE_H__

// SAGE Includes
#include <SAGE\Events.hpp>
#include <SAGE\Vector2.hpp>

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
			static void GetPosition(int& pX, int& pY);
			static void GetPosition(Vector2& pPosition);
			static Vector2 GetPosition();
			static void GetMovement(int& pX, int& pY);
			static void GetMovement(Vector2& pMovement);
			static Vector2 GetMovement();
			static bool IsButtonDown(MouseButton pButton);
			static bool IsButtonUp(MouseButton pButton);
			static bool IsButtonClicked(MouseButton pButton);
			static bool IsButtonReleased(MouseButton pButton);
			static bool IsScrolledUp();
			static bool IsScrolledDown();

		private:
			Mouse() = delete;
			~Mouse() = delete;

			static void Clear();
			static void SetPosition(int pX, int pY);
			static void SetScroll(int pX, int pY);
			static inline int ButtonMask(MouseButton pButton);

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
