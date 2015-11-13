// GamePad.cpp

// SAGE Includes
#include <SAGE/GamePad.hpp>

namespace SAGE
{
	std::map<PlayerIndex, GamePad*> GamePad::sGamePads;
	const Sint16 GamePad::MaxAxisRange = 32767;

	// static
	bool GamePad::IsButtonDown(PlayerIndex p_Index, GamePadButton p_Button)
	{
		if (sGamePads.find(p_Index) == sGamePads.end())
			return false;

		return sGamePads[p_Index]->IsButtonDown(p_Button);
	}

	// static
	bool GamePad::IsButtonUp(PlayerIndex p_Index, GamePadButton p_Button)
	{
		if (sGamePads.find(p_Index) == sGamePads.end())
			return false;

		return sGamePads[p_Index]->IsButtonUp(p_Button);
	}

	// static
	bool GamePad::IsButtonPressed(PlayerIndex p_Index, GamePadButton p_Button)
	{
		if (sGamePads.find(p_Index) == sGamePads.end())
			return false;

		return sGamePads[p_Index]->IsButtonPressed(p_Button);
	}

	// static
	bool GamePad::IsButtonReleased(PlayerIndex p_Index, GamePadButton p_Button)
	{
		if (sGamePads.find(p_Index) == sGamePads.end())
			return false;

		return sGamePads[p_Index]->IsButtonReleased(p_Button);
	}

	// static
	Sint16 GamePad::GetAxis(PlayerIndex p_Index, GamePadAxis p_Axis)
	{
		if (sGamePads.find(p_Index) == sGamePads.end())
			return false;

		return sGamePads[p_Index]->GetAxis(p_Axis);
	}

	GamePad::GamePad(PlayerIndex p_Index, SDL_GameController* p_Mapping)
	{
		m_Index = p_Index;
		m_Mapping = p_Mapping;
	}

	GamePad::~GamePad()
	{
		m_Index = PlayerIndex::Invalid;
		m_Mapping = nullptr;
	}

	void GamePad::Clear()
	{
		m_CurrentButtons = m_PreviousButtons;
		m_CurrentAxes = m_PreviousAxes;
	}

	PlayerIndex GamePad::GetIndex() const
	{
		return m_Index;
	}

	SDL_GameController* GamePad::GetMapping() const
	{
		return m_Mapping;
	}

	bool GamePad::IsButtonDown(GamePadButton p_Button)
	{
		return m_CurrentButtons[p_Button];
	}

	bool GamePad::IsButtonUp(GamePadButton p_Button)
	{
		return !m_CurrentButtons[p_Button];
	}

	bool GamePad::IsButtonPressed(GamePadButton p_Button)
	{
		return !m_PreviousButtons[p_Button] && m_CurrentButtons[p_Button];
	}

	bool GamePad::IsButtonReleased(GamePadButton p_Button)
	{
		return m_PreviousButtons[p_Button] && !m_CurrentButtons[p_Button];
	}

	Sint16 GamePad::GetAxis(GamePadAxis p_Axis)
	{
		return m_CurrentAxes[p_Axis];
	}

	void GamePad::SetButton(GamePadButton p_Button, bool p_State)
	{
		m_CurrentButtons[p_Button] = p_State;
	}

	void GamePad::SetAxis(GamePadAxis p_Axis, Sint16 p_Value)
	{
		m_CurrentAxes[p_Axis] = p_Value;
	}

	// static
	void GamePad::ClearAll()
	{
		for (auto& gp : sGamePads)
			gp.second->Clear();
	}

	// static
	void GamePad::Open(PlayerIndex p_Index)
	{
		// Check if it's already open.
		if (sGamePads.find(p_Index) != sGamePads.end())
			return;

		// Open the game controller.
		SDL_GameController* gc = SDL_GameControllerOpen(static_cast<int>(p_Index));

		// Add to map if it opened successfully.
		if (gc != nullptr)
			sGamePads[p_Index] = new GamePad(p_Index, gc);
	}

	// static
	void GamePad::Close(PlayerIndex p_Index)
	{
		// Close the game controller.
		SDL_GameControllerClose(sGamePads[p_Index]->GetMapping());

		// Free the GamePad memory.
		delete sGamePads[p_Index];

		// Remove from the map.
		sGamePads.erase(sGamePads.find(p_Index));
	}

	// static
	void GamePad::Remap(PlayerIndex p_Index)
	{
		// TODO
	}

	// static
	void GamePad::SetButton(PlayerIndex p_Index, GamePadButton p_Button, bool p_State)
	{
		sGamePads[p_Index]->SetButton(p_Button, p_State);
	}

	// static
	void GamePad::SetAxis(PlayerIndex p_Index, GamePadAxis p_Axis, Sint16 p_Value)
	{
		sGamePads[p_Index]->SetAxis(p_Axis, p_Value);
	}
}
