// MenuScreen.hpp

#ifndef __SAGE_MENUSCREEN_HPP__
#define __SAGE_MENUSCREEN_HPP__

// Project Includes
#include <SAGE\Screen.hpp>

namespace SAGE
{
	class MenuScreen : public Screen
	{
		public:
			MenuScreen();
			virtual ~MenuScreen();

			virtual int Update(float pDeltaTime) = 0;
			virtual int Render() = 0;
	};
}

#endif