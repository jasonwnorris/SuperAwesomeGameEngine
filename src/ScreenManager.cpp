// ScreenManager.cpp

// SAGE Includes
#include <SAGE\ScreenManager.hpp>

namespace SAGE
{
	ScreenManager::ScreenManager()
	{
		mScreenToPush = nullptr;
		mPushPause = true;
		mPushHide = true;
		mPopCount = 0;
	}

	ScreenManager::~ScreenManager()
	{
		for (int i = (int)mScreens.size() - 1; i >= 0; --i)
		{
			mScreens[i]->Finalize();

			delete mScreens[i];
		}

		mScreens.clear();

		if (mScreenToPush != nullptr)
		{
			mScreenToPush->Finalize();

			delete mScreenToPush;
		}
	}

	bool ScreenManager::IsEmpty() const
	{
		return mScreens.size() == 0 && mScreenToPush == nullptr;
	}

	int ScreenManager::Push(Screen* pScreen, bool pPause, bool pHide)
	{
		if (mScreenToPush != nullptr)
		{
			return -1;
		}

		mScreenToPush = pScreen;
		mPushPause = pPause;
		mPushHide = pHide;

		return 0;
	}

	int ScreenManager::Pop()
	{
		++mPopCount;

		return 0;
	}

	int ScreenManager::PopAll()
	{
		mPopCount = (int)mScreens.size();

		return 0;
	}

	int ScreenManager::Update(float pDeltaTime)
	{
		// Pop requested screens.
		while (mPopCount > 0 && (int)mScreens.size() != 0)
		{
			Screen* screen = mScreens.back();
			screen->Finalize();

			mScreens.pop_back();

			delete screen;

			--mPopCount;
		}

		mPopCount = 0;

		// Alter new top of stack if one exists.
		if (mScreens.size() > 0)
		{
			if (mScreens.back()->Resume() < 0)
			{
				return -1;
			}

			mScreens.back()->SetActive(true);
			mScreens.back()->SetVisible(true);
		}

		// Push new screen.
		if (mScreenToPush != nullptr)
		{
			// Alter previous top of stack.
			if (mScreens.size() > 0)
			{
				if (mPushPause && mPushHide)
				{
					if (mScreens.back()->Pause() < 0)
					{
						return -1;
					}
				}

				mScreens.back()->SetActive(!mPushPause);
				mScreens.back()->SetVisible(!mPushHide);
			}

			// Add to stack.
			if (mScreenToPush->Initialize() < 0)
			{
				mScreenToPush->Finalize();

				delete mScreenToPush;

				return -1;
			}
			else
			{
				mScreens.push_back(mScreenToPush);
			}

			mScreenToPush = nullptr;
		}

		// Update
		for (int i = 0; i < (int)mScreens.size(); ++i)
		{
			if (mScreens[i]->IsActive())
			{
				if (mScreens[i]->Update(pDeltaTime) < 0)
					return -1;
			}
		}

		return 0;
	}

	int ScreenManager::Render(SpriteBatch& pSpriteBatch)
	{
		// Render
		for (int i = 0; i < (int)mScreens.size(); ++i)
		{
			if (mScreens[i]->IsVisible())
			{
				if (mScreens[i]->Render(pSpriteBatch) < 0)
					return -1;
			}
		}

		return 0;
	}

	int ScreenManager::Render(GeometryBatch& pGeometryBatch)
	{
		// Render
		for (int i = 0; i < (int)mScreens.size(); ++i)
		{
			if (mScreens[i]->IsVisible())
			{
				if (mScreens[i]->Render(pGeometryBatch) < 0)
					return -1;
			}
		}

		return 0;
	}
}
