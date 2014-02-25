// Game.hpp

#ifndef __SAGE_GAME_HPP__
#define __SAGE_GAME_HPP__

// HGF Includes
#include <HGF\Window.hpp>
#include <HGF\Renderer.hpp>
#include <HGF\Timer.hpp>

namespace SAGE
{
	class Game
	{
		public:
			Game();
			virtual ~Game();

			virtual int Run();

			virtual int Update(float pDeltaTime) = 0;
			virtual int Render() = 0;

		protected:
			HGF::Window mWindow;
			HGF::Renderer mRenderer;
			HGF::Timer mTimer;
			bool mRunning;
	};
}

#endif