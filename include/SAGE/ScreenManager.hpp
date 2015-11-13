// ScreenManager.hpp

#ifndef __SAGE_SCREENMANAGER_HPP__
#define __SAGE_SCREENMANAGER_HPP__

// SAGE Includes
#include <SAGE/Screen.hpp>
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
			int Push(Screen* p_Screen, bool p_Pause = true, bool p_Hide = true);
			int Pop();
			int PopAll();

			int Update(float p_DeltaTime);
			int Render(SpriteBatch& p_SpriteBatch);
			int Render(GeometryBatch& p_GeometryBatch);

		private:
			std::vector<Screen*> m_Screens;
			Screen* m_ScreenToPush;
			bool m_PushPause;
			bool m_PushHide;
			int m_PopCount;
	};
}

#endif
