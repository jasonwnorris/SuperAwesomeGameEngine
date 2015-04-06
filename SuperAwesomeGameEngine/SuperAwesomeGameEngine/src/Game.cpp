// Game.cpp

// HGF Includes
#include <HGF\Events.hpp>
// Project Includes
#include <SAGE\Game.hpp>

namespace SAGE
{
	Game::Game()
	{
		mRunning = true;
	}

	Game::~Game()
	{

	}

	int Game::Run()
	{
		mTimer.Start();

		if (Initialize() < 0)
			return -1;

		while (mRunning)
		{
			HGF::Events::Poll();

			if (Update(mTimer.GetDeltaTime()) < 0)
				return -1;

			if (Render() < 0)
				return -1;
		}

		if (Finalize() < 0)
			return - 1;

		return 0;
	}
}