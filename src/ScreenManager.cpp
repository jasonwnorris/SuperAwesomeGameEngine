// ScreenManager.cpp

// SAGE Includes
#include <SAGE/ScreenManager.hpp>

namespace SAGE
{
	ScreenManager::ScreenManager(Game* p_Game) : IGameComponent(p_Game)
	{
		m_ScreenToPush = nullptr;
		m_PushPause = true;
		m_PushHide = true;
		m_PopCount = 0;
	}

	ScreenManager::~ScreenManager()
	{
		for (int i = (int)m_Screens.size() - 1; i >= 0; --i)
		{
			m_Screens[i]->Finalize();

			delete m_Screens[i];
		}

		m_Screens.clear();

		if (m_ScreenToPush != nullptr)
		{
			m_ScreenToPush->Finalize();

			delete m_ScreenToPush;
		}
	}

	bool ScreenManager::IsEmpty() const
	{
		return m_Screens.size() == 0 && m_ScreenToPush == nullptr;
	}

	int ScreenManager::Push(Screen* p_Screen, bool p_Pause, bool p_Hide)
	{
		if (m_ScreenToPush != nullptr)
		{
			return -1;
		}

		m_ScreenToPush = p_Screen;
		m_PushPause = p_Pause;
		m_PushHide = p_Hide;

		return 0;
	}

	int ScreenManager::Pop()
	{
		++m_PopCount;

		return 0;
	}

	int ScreenManager::PopAll()
	{
		m_PopCount = (int)m_Screens.size();

		return 0;
	}

	int ScreenManager::Update(float p_DeltaTime)
	{
		// Pop requested screens.
		while (m_PopCount > 0 && (int)m_Screens.size() != 0)
		{
			Screen* screen = m_Screens.back();
			screen->Finalize();

			m_Screens.pop_back();

			delete screen;

			--m_PopCount;
		}

		m_PopCount = 0;

		// Alter new top of stack if one exists.
		if (m_Screens.size() > 0)
		{
			if (m_Screens.back()->Resume() < 0)
			{
				return -1;
			}

			m_Screens.back()->SetActive(true);
			m_Screens.back()->SetVisible(true);
		}

		// Push new screen.
		if (m_ScreenToPush != nullptr)
		{
			// Alter previous top of stack.
			if (m_Screens.size() > 0)
			{
				if (m_PushPause && m_PushHide)
				{
					if (m_Screens.back()->Pause() < 0)
					{
						return -1;
					}
				}

				m_Screens.back()->SetActive(!m_PushPause);
				m_Screens.back()->SetVisible(!m_PushHide);
			}

			// Add to stack.
			if (m_ScreenToPush->Initialize() < 0)
			{
				m_ScreenToPush->Finalize();

				delete m_ScreenToPush;

				return -1;
			}
			else
			{
				m_Screens.push_back(m_ScreenToPush);
			}

			m_ScreenToPush = nullptr;
		}

		// Update
		for (int i = 0; i < (int)m_Screens.size(); ++i)
		{
			if (m_Screens[i]->IsActive())
			{
				if (m_Screens[i]->Update(p_DeltaTime) < 0)
					return -1;
			}
		}

		return 0;
	}

	int ScreenManager::Render(SpriteBatch& p_SpriteBatch)
	{
		// Render
		for (int i = 0; i < (int)m_Screens.size(); ++i)
		{
			if (m_Screens[i]->IsVisible())
			{
				if (m_Screens[i]->Render(p_SpriteBatch) < 0)
					return -1;
			}
		}

		return 0;
	}

	int ScreenManager::Render(GeometryBatch& p_GeometryBatch)
	{
		// Render
		for (int i = 0; i < (int)m_Screens.size(); ++i)
		{
			if (m_Screens[i]->IsVisible())
			{
				if (m_Screens[i]->Render(p_GeometryBatch) < 0)
					return -1;
			}
		}

		return 0;
	}
}
