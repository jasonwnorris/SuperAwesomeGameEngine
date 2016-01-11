// Game.cpp

// SAGE Includes
#include <SAGE/Game.hpp>
#include <SAGE/Events.hpp>

namespace SAGE
{
	Game::Game()
	{
		m_Window = new Window(this);
		m_ScreenManager = new ScreenManager(this);
	}

	Game::~Game()
	{
		if (m_Window != nullptr)
		{
			delete m_Window;
		}

		if (m_ScreenManager != nullptr)
		{
			delete m_ScreenManager;
		}
	}

	Window* Game::GetWindow() const
	{
		return m_Window;
	}

	ScreenManager* Game::GetScreenManager() const
	{
		return m_ScreenManager;
	}

	int Game::Start()
	{
		m_Running = true;

		if (Initialize() < 0)
			return -1;

		while (m_Running)
		{
			Events::Poll();

			if (Update(m_Timer.GetDeltaTime()) < 0)
				return -1;

			m_Window->Clear();

			if (Render(m_SpriteBatch) < 0)
				return -1;

			if (Render(m_GeometryBatch) < 0)
				return -1;

			m_Window->Flip();
		}

		if (Finalize() < 0)
			return - 1;

		return 0;
	}

	void Game::Quit()
	{
		m_Running = false;
	}

	int Game::Initialize()
	{
		m_Timer.Start();

		if (!m_Window->Initialize())
			return -1;

		if (!m_SpriteBatch.Initialize())
			return -1;

		if (!m_GeometryBatch.Initialize())
			return -1;

		return 0;
	}

	int Game::Finalize()
	{
		if (!m_SpriteBatch.Finalize())
			return -1;

		if (!m_GeometryBatch.Finalize())
			return -1;

		if (!m_Window->Finalize())
			return -1;

		return 0;
	}

	int Game::Render(SpriteBatch& p_SpriteBatch)
	{
		return 0;
	}

	int Game::Render(GeometryBatch& p_GeometryBatch)
	{
		return 0;
	}
}
