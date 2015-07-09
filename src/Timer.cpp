// Timer.cpp

// SAGE Includes
#include <SAGE\Timer.hpp>

namespace SAGE
{
	Timer::Timer()
	{
		Stop();
	}

	Timer::~Timer()
	{
	}

	float Timer::GetDeltaTime()
	{
		if (!m_Started || m_Paused)
			return 0.0f;

		Uint32 current = SDL_GetTicks();
		Uint32 difference = current - m_LastTicks;
		m_LastTicks = current;

		return (float)(difference / 1000.0f);
	}

	float Timer::GetElapsedTime() const
	{
		if (!m_Started)
			return 0.0f;

		if (m_Paused)
			return (float)m_PausedTicks;
		else
			return (float)((SDL_GetTicks() - m_StartTicks) / 1000.0f);
	}

	int Timer::GetTicks() const
	{
		if (!m_Started)
			return 0;

		if (m_Paused)
			return m_PausedTicks;
		else
			return (SDL_GetTicks() - m_StartTicks);
	}

	void Timer::Start()
	{
		m_StartTicks = SDL_GetTicks();
		m_LastTicks = m_StartTicks;
		m_PausedTicks = 0;
		m_Started = true;
		m_Paused = false;
	}

	void Timer::Stop()
	{
		m_Started = false;
		m_Paused = false;
	}

	void Timer::Pause()
	{
		if (m_Started && !m_Paused)
		{
			m_PausedTicks = SDL_GetTicks() - m_StartTicks;
			m_Paused = true;
		}
	}

	void Timer::Resume()
	{
		if (m_Paused)
		{
			m_StartTicks = SDL_GetTicks() - m_PausedTicks;
			m_PausedTicks = 0;
			m_Paused = false;
		}
	}
}
