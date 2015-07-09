// Game.cpp

// SAGE Includes
#include <SAGE\Game.hpp>
#include <SAGE\Events.hpp>

namespace SAGE
{
	Game::Game()
	{
	}

	Game::~Game()
	{
	}

	int Game::Start()
	{
		mRunning = true;

		if (Initialize() < 0)
			return -1;

		while (mRunning)
		{
			Events::Poll();

			if (Update(mTimer.GetDeltaTime()) < 0)
				return -1;

			mWindow.Clear();

			if (Render(mSpriteBatch) < 0)
				return -1;

			if (Render(mGeometryBatch) < 0)
				return -1;

			mWindow.Flip();
		}

		if (Finalize() < 0)
			return - 1;

		return 0;
	}

	void Game::Quit()
	{
		mRunning = false;
	}

	int Game::Initialize()
	{
		mTimer.Start();

		if (!mWindow.Initialize())
			return -1;

		if (!mSpriteBatch.Initialize())
			return -1;

		if (!mGeometryBatch.Initialize())
			return -1;

		return 0;
	}

	int Game::Finalize()
	{
		if (!mSpriteBatch.Finalize())
			return -1;

		if (!mGeometryBatch.Finalize())
			return -1;

		if (!mWindow.Finalize())
			return -1;

		return 0;
	}

	int Game::Render(SpriteBatch& pSpriteBatch)
	{
		return 0;
	}

	int Game::Render(GeometryBatch& pGeometryBatch)
	{
		return 0;
	}
}
