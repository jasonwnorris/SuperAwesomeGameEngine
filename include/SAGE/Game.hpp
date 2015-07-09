// Game.hpp

#ifndef __SAGE_GAME_HPP__
#define __SAGE_GAME_HPP__

// SAGE Includes
#include <SAGE\GeometryBatch.hpp>
#include <SAGE\SpriteBatch.hpp>
#include <SAGE\ScreenManager.hpp>
// SAGE Includes
#include <SAGE\Timer.hpp>
#include <SAGE\Window.hpp>

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

			Window mWindow;
			ScreenManager mScreenManager;

		private:
			Timer mTimer;
			SpriteBatch mSpriteBatch;
			GeometryBatch mGeometryBatch;
			bool mRunning;
	};
}

#endif
