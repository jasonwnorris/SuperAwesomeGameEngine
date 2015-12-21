// Timer.hpp

#ifndef __SAGE_TIMER_HPP__
#define __SAGE_TIMER_HPP__

// SDL Includes
#include <SDL2/SDL.h>

namespace SAGE
{
	class Timer
	{
		public:
			Timer();
			~Timer();

			float GetDeltaTime();
			float GetElapsedTime() const;
			int GetTicks() const;

			void Start();
			void Stop();
			void Pause();
			void Resume();

		private:
			Uint32 m_StartTicks;
			Uint32 m_LastTicks;
			Uint32 m_PausedTicks;
			bool m_Started;
			bool m_Paused;
	};
}

#endif
