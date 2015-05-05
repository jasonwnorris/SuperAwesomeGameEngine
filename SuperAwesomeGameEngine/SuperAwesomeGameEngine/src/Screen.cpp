// Screen.cpp

// Project Includes
#include <SAGE\Screen.hpp>

namespace SAGE
{
	Screen::Screen()
	{
	}

	Screen::~Screen()
	{
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
}