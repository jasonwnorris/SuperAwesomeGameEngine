// GamePad.cpp

// SAGE Includes
#include <SAGE\GamePad.hpp>

namespace SAGE
{
	std::map<PlayerIndex, GamePad*> GamePad::sGamePads;
	const Sint16 GamePad::MaxAxisRange = 32767;

	// static
	bool GamePad::IsButtonDown(PlayerIndex pIndex, GamePadButton pButton)
	{
		if (sGamePads.find(pIndex) == sGamePads.end())
			return false;

		return sGamePads[pIndex]->IsButtonDown(pButton);
	}

	// static
	bool GamePad::IsButtonUp(PlayerIndex pIndex, GamePadButton pButton)
	{
		if (sGamePads.find(pIndex) == sGamePads.end())
			return false;

		return sGamePads[pIndex]->IsButtonUp(pButton);
	}

	// static
	bool GamePad::IsButtonPressed(PlayerIndex pIndex, GamePadButton pButton)
	{
		if (sGamePads.find(pIndex) == sGamePads.end())
			return false;

		return sGamePads[pIndex]->IsButtonPressed(pButton);
	}

	// static
	bool GamePad::IsButtonReleased(PlayerIndex pIndex, GamePadButton pButton)
	{
		if (sGamePads.find(pIndex) == sGamePads.end())
			return false;

		return sGamePads[pIndex]->IsButtonReleased(pButton);
	}

	// static
	Sint16 GamePad::GetAxis(PlayerIndex pIndex, GamePadAxis pAxis)
	{
		if (sGamePads.find(pIndex) == sGamePads.end())
			return false;

		return sGamePads[pIndex]->GetAxis(pAxis);
	}

	GamePad::GamePad(PlayerIndex pIndex, SDL_GameController* pMapping)
	{
		mIndex = pIndex;
		mMapping = pMapping;
	}

	GamePad::~GamePad()
	{
		mIndex = PlayerIndex::Invalid;
		mMapping = nullptr;
	}

	void GamePad::Clear()
	{
		mCurrentButtons = mPreviousButtons;
		mCurrentAxes = mPreviousAxes;
	}

	PlayerIndex GamePad::GetIndex() const
	{
		return mIndex;
	}

	SDL_GameController* GamePad::GetMapping() const
	{
		return mMapping;
	}

	bool GamePad::IsButtonDown(GamePadButton pButton)
	{
		return mCurrentButtons[pButton];
	}

	bool GamePad::IsButtonUp(GamePadButton pButton)
	{
		return !mCurrentButtons[pButton];
	}

	bool GamePad::IsButtonPressed(GamePadButton pButton)
	{
		return !mPreviousButtons[pButton] && mCurrentButtons[pButton];
	}

	bool GamePad::IsButtonReleased(GamePadButton pButton)
	{
		return mPreviousButtons[pButton] && !mCurrentButtons[pButton];
	}

	Sint16 GamePad::GetAxis(GamePadAxis pAxis)
	{
		return mCurrentAxes[pAxis];
	}

	void GamePad::SetButton(GamePadButton pButton, bool pState)
	{
		mCurrentButtons[pButton] = pState;
	}

	void GamePad::SetAxis(GamePadAxis pAxis, Sint16 pValue)
	{
		mCurrentAxes[pAxis] = pValue;
	}

	// static
	void GamePad::ClearAll()
	{
		for (auto& gp : sGamePads)
			gp.second->Clear();
	}

	// static
	void GamePad::Open(PlayerIndex pIndex)
	{
		// Check if it's already open.
		if (sGamePads.find(pIndex) != sGamePads.end())
			return;

		// Open the game controller.
		SDL_GameController* gc = SDL_GameControllerOpen(static_cast<int>(pIndex));

		// Add to map if it opened successfully.
		if (gc != nullptr)
			sGamePads[pIndex] = new GamePad(pIndex, gc);
	}

	// static
	void GamePad::Close(PlayerIndex pIndex)
	{
		// Close the game controller.
		SDL_GameControllerClose(sGamePads[pIndex]->GetMapping());

		// Free the GamePad memory.
		delete sGamePads[pIndex];

		// Remove from the map.
		sGamePads.erase(sGamePads.find(pIndex));
	}

	// static
	void GamePad::Remap(PlayerIndex pIndex)
	{
		// TODO
	}

	// static
	void GamePad::SetButton(PlayerIndex pIndex, GamePadButton pButton, bool pState)
	{
		sGamePads[pIndex]->SetButton(pButton, pState);
	}

	// static
	void GamePad::SetAxis(PlayerIndex pIndex, GamePadAxis pAxis, Sint16 pValue)
	{
		sGamePads[pIndex]->SetAxis(pAxis, pValue);
	}
}
