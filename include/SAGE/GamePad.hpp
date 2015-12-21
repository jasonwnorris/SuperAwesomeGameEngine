// GamePad.hpp

#ifndef __SAGE_GAMEPAD_H__
#define __SAGE_GAMEPAD_H__

// SDL Includes
#include <SDL2/SDL.h>
// STD Includes
#include <map>

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
			static bool IsButtonDown(PlayerIndex p_Index, GamePadButton p_Button);
			static bool IsButtonUp(PlayerIndex p_Index, GamePadButton p_Button);
			static bool IsButtonPressed(PlayerIndex p_Index, GamePadButton p_Button);
			static bool IsButtonReleased(PlayerIndex p_Index, GamePadButton p_Button);
			static Sint16 GetAxis(PlayerIndex p_Index, GamePadAxis p_Axis);

		private:
			GamePad(PlayerIndex p_Index, SDL_GameController* p_Mapping);
			~GamePad();

			void Clear();
			PlayerIndex GetIndex() const;
			SDL_GameController* GetMapping() const;
			bool IsButtonDown(GamePadButton p_Button);
			bool IsButtonUp(GamePadButton p_Button);
			bool IsButtonPressed(GamePadButton p_Button);
			bool IsButtonReleased(GamePadButton p_Button);
			Sint16 GetAxis(GamePadAxis p_Axis);

			void SetButton(GamePadButton p_Button, bool p_State);
			void SetAxis(GamePadAxis p_Axis, Sint16 p_Value);

			static void ClearAll();
			static void Open(PlayerIndex p_Index);
			static void Close(PlayerIndex p_Index);
			static void Remap(PlayerIndex p_Index);
			static void SetButton(PlayerIndex p_Index, GamePadButton p_Button, bool p_State);
			static void SetAxis(PlayerIndex p_Index, GamePadAxis p_Axis, Sint16 p_Value);

			static std::map<PlayerIndex, GamePad*> sGamePads;
			static const Sint16 MaxAxisRange;
			
			PlayerIndex m_Index;
			SDL_GameController* m_Mapping;
			std::map<GamePadButton, bool> m_CurrentButtons;
			std::map<GamePadButton, bool> m_PreviousButtons;
			std::map<GamePadAxis, Sint16> m_CurrentAxes;
			std::map<GamePadAxis, Sint16> m_PreviousAxes;

	};
}

#endif
