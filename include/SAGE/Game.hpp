// Game.hpp

#ifndef __SAGE_GAME_HPP__
#define __SAGE_GAME_HPP__

// SAGE Includes
#include <SAGE\GeometryBatch.hpp>
#include <SAGE\SpriteBatch.hpp>
#include <SAGE\ScreenManager.hpp>
// HGF Includes
#include <HGF\Timer.hpp>
#include <HGF\Window.hpp>

namespace SAGE
{
	class Game
	{
		public:
			Game();
			virtual ~Game();

			int Start();
			void Quit();

		protected:
			virtual int Initialize();
			virtual int Finalize();

			virtual int Update(float pDeltaTime) = 0;
			virtual int Render(SpriteBatch& pSpriteBatch);
			virtual int Render(GeometryBatch& pGeometryBatch);

			HGF::Window mWindow;
			ScreenManager mScreenManager;

		private:
			HGF::Timer mTimer;
			SpriteBatch mSpriteBatch;
			GeometryBatch mGeometryBatch;
			bool mRunning;
	};
}

#endif