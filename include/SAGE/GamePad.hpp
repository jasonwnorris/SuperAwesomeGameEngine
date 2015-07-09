// GamePad.hpp

#ifndef __SAGE_GAMEPAD_H__
#define __SAGE_GAMEPAD_H__

// STD Includes
#include <map>
// SDL Includes
#include <SDL2\SDL.h>

namespace SAGE
{
	enum class PlayerIndex : int
	{
		Invalid = -1,
		One = 0,
		Two = 1,
		Three = 2,
		Four = 3,
	};

	enum class GamePadButton : Uint8
	{
		A = SDL_CONTROLLER_BUTTON_A,
		B = SDL_CONTROLLER_BUTTON_B,
		X = SDL_CONTROLLER_BUTTON_X,
		Y = SDL_CONTROLLER_BUTTON_Y,
		Start = SDL_CONTROLLER_BUTTON_START,
		Back = SDL_CONTROLLER_BUTTON_BACK,
		Guide = SDL_CONTROLLER_BUTTON_GUIDE,
		LeftShoulder = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
		RightShoulder = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
		LeftStick = SDL_CONTROLLER_BUTTON_LEFTSTICK,
		RightStick = SDL_CONTROLLER_BUTTON_RIGHTSTICK,
		DirectionUp = SDL_CONTROLLER_BUTTON_DPAD_UP,
		DirectionDown = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
		DirectionLeft = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
		DirectionRight = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
	};

	enum class GamePadAxis : Uint8
	{
		LeftX = SDL_CONTROLLER_AXIS_LEFTX,
		LeftY = SDL_CONTROLLER_AXIS_LEFTY,
		RightX = SDL_CONTROLLER_AXIS_RIGHTX,
		RightY = SDL_CONTROLLER_AXIS_RIGHTY,
		TriggerLeft = SDL_CONTROLLER_AXIS_TRIGGERLEFT,
		TriggerRight = SDL_CONTROLLER_AXIS_TRIGGERRIGHT,
	};

	class GamePad
	{
		friend class Events;

		public:
			static bool IsButtonDown(PlayerIndex pIndex, GamePadButton pButton);
			static bool IsButtonUp(PlayerIndex pIndex, GamePadButton pButton);
			static bool IsButtonPressed(PlayerIndex pIndex, GamePadButton pButton);
			static bool IsButtonReleased(PlayerIndex pIndex, GamePadButton pButton);
			static Sint16 GetAxis(PlayerIndex pIndex, GamePadAxis pAxis);

		private:
			GamePad(PlayerIndex pIndex, SDL_GameController* pMapping);
			~GamePad();

			void Clear();
			PlayerIndex GetIndex() const;
			SDL_GameController* GetMapping() const;
			bool IsButtonDown(GamePadButton pButton);
			bool IsButtonUp(GamePadButton pButton);
			bool IsButtonPressed(GamePadButton pButton);
			bool IsButtonReleased(GamePadButton pButton);
			Sint16 GetAxis(GamePadAxis pAxis);

			void SetButton(GamePadButton pButton, bool pState);
			void SetAxis(GamePadAxis pAxis, Sint16 pValue);

			static void ClearAll();
			static void Open(PlayerIndex pIndex);
			static void Close(PlayerIndex pIndex);
			static void Remap(PlayerIndex pIndex);
			static void SetButton(PlayerIndex pIndex, GamePadButton pButton, bool pState);
			static void SetAxis(PlayerIndex pIndex, GamePadAxis pAxis, Sint16 pValue);

			static std::map<PlayerIndex, GamePad*> sGamePads;
			static const Sint16 MaxAxisRange;
			
			PlayerIndex mIndex;
			SDL_GameController* mMapping;
			std::map<GamePadButton, bool> mCurrentButtons;
			std::map<GamePadButton, bool> mPreviousButtons;
			std::map<GamePadAxis, Sint16> mCurrentAxes;
			std::map<GamePadAxis, Sint16> mPreviousAxes;

	};
}

#endif
