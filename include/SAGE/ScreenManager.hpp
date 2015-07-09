// ScreenManager.hpp

#ifndef __SAGE_SCREENMANAGER_HPP__
#define __SAGE_SCREENMANAGER_HPP__

// SAGE Includes
#include <SAGE\Screen.hpp>
// STL Includes
#include <vector>

namespace SAGE
{
	class ScreenManager
	{
		public:
			ScreenManager();
			~ScreenManager();

			bool IsEmpty() const;
			int Push(Screen* pScreen, bool pPause = true, bool pHide = true);
			int Pop();
			int PopAll();

			int Update(float pDeltaTime);
			int Render(SpriteBatch& pSpriteBatch);
			int Render(GeometryBatch& pGeometryBatch);

		private:
			std::vector<Screen*> mScreens;
			Screen* mScreenToPush;
			bool mPushPause;
			bool mPushHide;
			int mPopCount;
	};
}

#endif
