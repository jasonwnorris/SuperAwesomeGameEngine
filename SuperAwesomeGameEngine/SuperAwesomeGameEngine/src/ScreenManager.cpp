// ScreenManager.cpp

// Project Includes
#include <SAGE\ScreenManager.hpp>

namespace SAGE
{
	ScreenManager::ScreenManager()
	{
	}

	ScreenManager::~ScreenManager()
	{
		for (int i = (int)mScreens.size() - 1; i >= 0; --i)
		{
			mScreens[i]->Finalize();
			
			delete mScreens[i];
		}

		mScreens.clear();
	}

	int ScreenManager::Push(Screen* pScreen)
	{
		if (pScreen->Initialize() < 0)
		{
			pScreen->Finalize();

			delete pScreen;

			return -1;
		}

		if (mScreens.size() > 0)
		{
			// mScreen.Hide()?
			mScreens.back()->SetActive(false);
			mScreens.back()->SetVisible(false);
		}

		mScreens.push_back(pScreen);

		return 0;
	}

	int ScreenManager::Pop()
	{
		if (mScreens.size() == 0)
		{
			return -1;
		}

		// Remove top.
		Screen* screen = mScreens.back();
		screen->Finalize();
		delete screen;
		mScreens.pop_back();

		// Alter new top.
		// mScreen.Restore()?
		mScreens.back()->SetActive(true);
		mScreens.back()->SetVisible(true);

		return 0;
	}

	int ScreenManager::PopAll()
	{
		while (mScreens.size() > 0)
		{
			if (Pop() < 0)
			{
				return -1;
			}
		}

		return 0;
	}

	int ScreenManager::Update(float pDeltaTime)
	{
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