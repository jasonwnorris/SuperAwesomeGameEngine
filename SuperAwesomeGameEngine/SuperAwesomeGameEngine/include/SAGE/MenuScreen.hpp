// MenuScreen.hpp

#ifndef __SAGE_MENUSCREEN_HPP__
#define __SAGE_MENUSCREEN_HPP__

// Project Includes
#include <SAGE\Screen.hpp>
// STL Includes
#include <string>
#include <vector>

namespace SAGE
{
	class MenuScreen : public Screen
	{
		public:
			MenuScreen();
			virtual ~MenuScreen();

			virtual int Update(float pDeltaTime) override;
			virtual int Render(SpriteBatch& pSpriteBatch) override;

		private:
			std::vector<std::string> mItems;
	};
}

#endif