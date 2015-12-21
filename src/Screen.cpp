// Screen.cpp

// SAGE Includes
#include <SAGE/Screen.hpp>

namespace SAGE
{
	Screen::Screen(ScreenManager* p_Manager)
	{
		m_Manager = p_Manager;
		m_TransitionState = TransitionState::On;
		m_IsActive = true;
		m_IsVisible = true;
	}

	Screen::~Screen()
	{
		m_Manager = nullptr;
	}

	bool Screen::IsActive() const
	{
		return m_IsActive;
	}

	bool Screen::IsVisible() const
	{
		return m_IsVisible;
	}

	void Screen::SetActive(bool p_Active)
	{
		m_IsActive = p_Active;
	}

	void Screen::SetVisible(bool p_Visible)
	{
		m_IsVisible = p_Visible;
	}

	int Screen::Initialize()
	{
		return 0;
	}

	int Screen::Finalize()
	{
		return 0;
	}

	int Screen::Pause()
	{
		return 0;
	}

	int Screen::Resume()
	{
		return 0;
	}

	int Screen::Render(GeometryBatch& p_GeometryBatch)
	{
		return 0;
	}
}
