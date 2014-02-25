// Screen.hpp

#ifndef __SAGE_SCREEN_HPP__
#define __SAGE_SCREEN_HPP__

namespace SAGE
{
	class Screen
	{
		public:
			Screen();
			virtual ~Screen();

			virtual int Update(float pDeltaTime) = 0;
			virtual int Render() = 0;
	};
}

#endif