// Screen.cpp

// SAGE Includes
#include <SAGE\Screen.hpp>

namespace SAGE
{
	Screen::Screen(ScreenManager* pManager)
	{
		mManager = pManager;
		mTransitionState = TransitionState::On;
		mIsActive = true;
		mIsVisible = true;
	}

	Screen::~Screen()
	{
		mManager = nullptr;
	}

	bool Screen::IsActive() const
	{
		return mIsActive;
	}

	bool Screen::IsVisible() const
	{
		return mIsVisible;
	}

	void Screen::SetActive(bool pActive)
	{
		mIsActive = pActive;
	}

	void Screen::SetVisible(bool pVisible)
	{
		mIsVisible = pVisible;
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

	int Screen::Render(GeometryBatch& pGeometryBatch)
	{
		return 0;
	}
}
