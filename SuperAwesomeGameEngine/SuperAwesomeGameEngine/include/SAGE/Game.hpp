// Game.hpp

#ifndef __SAGE_GAME_HPP__
#define __SAGE_GAME_HPP__

// HGF Includes
#include <HGF\Timer.hpp>

namespace SAGE
{
	class Game
	{
		public:
			Game();
			virtual ~Game();

			int Run();

		protected:
			virtual int Initialize() = 0;
			virtual int Finalize() = 0;

			virtual int Update(float pDeltaTime) = 0;
			virtual int Render() = 0;

		protected:
			HGF::Timer mTimer;
			bool mRunning;
	};
}

#endif