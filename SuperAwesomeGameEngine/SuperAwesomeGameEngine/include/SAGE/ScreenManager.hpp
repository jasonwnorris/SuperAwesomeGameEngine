// ScreenManager.hpp

#ifndef __SAGE_SCREENMANAGER_HPP__
#define __SAGE_SCREENMANAGER_HPP__

// Project Includes
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

			int Push(Screen* pScreen);
			int Pop();
			int PopAll();

			int Update(float pDeltaTime);
			int Render(SpriteBatch& pSpriteBatch);
			int Render(GeometryBatch& pGeometryBatch);

		private:
			std::vector<Screen*> mScreens;
	};
}

#endif