// MenuScreen.hpp

#ifndef __SAGE_MENUSCREEN_HPP__
#define __SAGE_MENUSCREEN_HPP__

// SAGE Includes
#include <SAGE\Screen.hpp>
// STL Includes
#include <string>
#include <vector>

namespace SAGE
{
	class MenuScreen : public Screen
	{
		public:
			MenuScreen(ScreenManager* p_Manager);
			virtual ~MenuScreen();

			virtual int Update(float p_DeltaTime) override;
			virtual int Render(SpriteBatch& p_SpriteBatch) override;

		private:
			std::vector<std::string> m_Items;
	};
}

#endif
