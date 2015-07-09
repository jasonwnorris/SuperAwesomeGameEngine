// AudioSource.cpp

// SAGE Includes
#include <SAGE\AudioSource.hpp>

namespace SAGE
{
	AudioSource::AudioSource()
	{
		m_PositionX = 0.0f;
		m_PositionY = 0.0f;
		m_VelocityX = 0.0f;
		m_VelocityY = 0.0f;
		m_Pitch = 1.0f;
		m_Gain = 1.0f;
		ALfloat ori[] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };

		alGenSources(1, &m_ID);

		alSource3f(m_ID, AL_POSITION, m_PositionX, m_PositionY, 0.0f);
		alSource3f(m_ID, AL_VELOCITY, m_VelocityX, m_VelocityY, 0.0f);
		alSourcefv(m_ID, AL_ORIENTATION, ori);
		alSourcef(m_ID, AL_PITCH, m_Pitch);
		alSourcef(m_ID, AL_GAIN, m_Gain);
		alSourcei(m_ID, AL_LOOPING, AL_TRUE);
	}

	AudioSource::AudioSource(ALuint p_BufferID)
	{
		m_PositionX = 0.0f;
		m_PositionY = 0.0f;
		m_VelocityX = 0.0f;
		m_VelocityY = 0.0f;
		m_Pitch = 1.0f;
		m_Gain = 1.0f;
		ALfloat ori[] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };

		alGenSources(1, &m_ID);

		alSource3f(m_ID, AL_POSITION, m_PositionX, m_PositionY, 0.0f);
		alSource3f(m_ID, AL_VELOCITY, m_VelocityX, m_VelocityY, 0.0f);
		alSourcefv(m_ID, AL_ORIENTATION, ori);
		alSourcef(m_ID, AL_PITCH, m_Pitch);
		alSourcef(m_ID, AL_GAIN, m_Gain);
		alSourcei(m_ID, AL_LOOPING, AL_TRUE);
		alSourcei(m_ID, AL_BUFFER, p_BufferID);
	}

	AudioSource::~AudioSource()
	{
		alDeleteSources(1, &m_ID);
	}

	void AudioSource::SetBuffer(ALuint p_BufferID)
	{
		if (p_BufferID != m_BufferID)
		{
			m_BufferID = p_BufferID;

			alSourcei(m_ID, AL_BUFFER, m_BufferID);
		}
	}

	void AudioSource::SetPosition(ALfloat p_PositionX, ALfloat p_PositionY)
	{
		m_PositionX = p_PositionX;
		m_PositionY = p_PositionY;

		alSource3f(m_ID, AL_POSITION, m_PositionX, m_PositionY, 0.0f);
	}

	void AudioSource::SetPosition(const Vector2& p_Position)
	{
		m_PositionX = p_Position.X;
		m_PositionY = p_Position.Y;

		alSource3f(m_ID, AL_POSITION, m_PositionX, m_PositionY, 0.0f);
	}

	void AudioSource::SetVelocity(ALfloat p_VelocityX, ALfloat p_VelocityY)
	{
		m_VelocityX = p_VelocityX;
		m_VelocityY = p_VelocityY;

		alSource3f(m_ID, AL_VELOCITY, m_VelocityX, m_VelocityY, 0.0f);
	}

	void AudioSource::SetVelocity(const Vector2& p_Velocity)
	{
		m_VelocityX = p_Velocity.X;
		m_VelocityY = p_Velocity.Y;

		alSource3f(m_ID, AL_VELOCITY, m_VelocityX, m_VelocityY, 0.0f);
	}

	void AudioSource::SetPitch(ALfloat p_Pitch)
	{
		m_Pitch = p_Pitch;

		alSourcef(m_ID, AL_PITCH, m_Pitch);
	}

	void AudioSource::SetGain(ALfloat p_Gain)
	{
		m_Gain = p_Gain;

		alSourcef(m_ID, AL_GAIN, m_Gain);
	}

	void AudioSource::SetLooping(ALboolean p_IsLooping)
	{
		m_IsLooping = p_IsLooping;

		alSourcei(m_ID, AL_LOOPING, m_IsLooping ? AL_TRUE : AL_FALSE);
	}

	void AudioSource::Play()
	{
		alSourcePlay(m_ID);
	}

	void AudioSource::Pause()
	{
		alSourcePause(m_ID);
	}

	void AudioSource::Stop()
	{
		alSourceStop(m_ID);
	}
}
