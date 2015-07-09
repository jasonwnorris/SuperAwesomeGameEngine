// AudioListener.cpp

// SAGE Includes
#include <SAGE\AudioListener.hpp>

namespace SAGE
{
	AudioListener::AudioListener()
	{
		m_PositionX = 0.0f;
		m_PositionY = 0.0f;
		m_VelocityX = 0.0f;
		m_VelocityY = 0.0f;
		ALfloat ori[] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };

		alListener3f(AL_POSITION, m_PositionX, m_PositionY, 0.0f);
		alListener3f(AL_VELOCITY, m_VelocityX, m_VelocityY, 0.0f);
		alListenerfv(AL_ORIENTATION, ori);
	}

	AudioListener::~AudioListener()
	{
	}

	void AudioListener::SetPosition(ALfloat p_PositionX, ALfloat p_PositionY)
	{
		m_PositionX = p_PositionX;
		m_PositionY = p_PositionY;

		alListener3f(AL_POSITION, m_PositionX, m_PositionY, 0.0f);
	}

	void AudioListener::SetPosition(const Vector2& p_Position)
	{
		m_PositionX = p_Position.X;
		m_PositionY = p_Position.Y;

		alListener3f(AL_POSITION, m_PositionX, m_PositionY, 0.0f);
	}

	void AudioListener::SetVelocity(ALfloat p_VelocityX, ALfloat p_VelocityY)
	{
		m_VelocityX = p_VelocityX;
		m_VelocityY = p_VelocityY;

		alListener3f(AL_VELOCITY, m_VelocityX, m_VelocityY, 0.0f);
	}

	void AudioListener::SetVelocity(const Vector2& p_Velocity)
	{
		m_VelocityX = p_Velocity.X;
		m_VelocityY = p_Velocity.Y;

		alListener3f(AL_VELOCITY, m_VelocityX, m_VelocityY, 0.0f);
	}
}
