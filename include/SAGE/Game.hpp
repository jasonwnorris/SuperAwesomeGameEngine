// Game.hpp

#ifndef __SAGE_GAME_HPP__
#define __SAGE_GAME_HPP__

// SAGE Includes
#include <SAGE/GeometryBatch.hpp>
#include <SAGE/SpriteBatch.hpp>
#include <SAGE/ScreenManager.hpp>
#include <SAGE/Timer.hpp>
#include <SAGE/Window.hpp>

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

			virtual int Update(float p_DeltaTime) = 0;
			virtual int Render(SpriteBatch& p_SpriteBatch);
			virtual int Render(GeometryBatch& p_GeometryBatch);

			Window m_Window;
			ScreenManager m_ScreenManager;

		private:
			Timer m_Timer;
			SpriteBatch m_SpriteBatch;
			GeometryBatch m_GeometryBatch;
			bool m_Running;
	};
}

#endif
