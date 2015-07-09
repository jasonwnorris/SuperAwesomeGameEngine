// AudioSource.cpp

// SAGE Includes
#include <SAGE\AudioSource.hpp>

namespace SAGE
{
	AudioSource::AudioSource()
	{
		mPositionX = 0.0f;
		mPositionY = 0.0f;
		mVelocityX = 0.0f;
		mVelocityY = 0.0f;
		mPitch = 1.0f;
		mGain = 1.0f;
		ALfloat ori[] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };

		alGenSources(1, &mID);

		alSource3f(mID, AL_POSITION, mPositionX, mPositionY, 0.0f);
		alSource3f(mID, AL_VELOCITY, mVelocityX, mVelocityY, 0.0f);
		alSourcefv(mID, AL_ORIENTATION, ori);
		alSourcef(mID, AL_PITCH, mPitch);
		alSourcef(mID, AL_GAIN, mGain);
		alSourcei(mID, AL_LOOPING, AL_TRUE);
	}

	AudioSource::AudioSource(ALuint pBufferID)
	{
		mPositionX = 0.0f;
		mPositionY = 0.0f;
		mVelocityX = 0.0f;
		mVelocityY = 0.0f;
		mPitch = 1.0f;
		mGain = 1.0f;
		ALfloat ori[] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };

		alGenSources(1, &mID);

		alSource3f(mID, AL_POSITION, mPositionX, mPositionY, 0.0f);
		alSource3f(mID, AL_VELOCITY, mVelocityX, mVelocityY, 0.0f);
		alSourcefv(mID, AL_ORIENTATION, ori);
		alSourcef(mID, AL_PITCH, mPitch);
		alSourcef(mID, AL_GAIN, mGain);
		alSourcei(mID, AL_LOOPING, AL_TRUE);
		alSourcei(mID, AL_BUFFER, pBufferID);
	}

	AudioSource::~AudioSource()
	{
		alDeleteSources(1, &mID);
	}

	void AudioSource::SetBuffer(ALuint pBufferID)
	{
		if (pBufferID != mBufferID)
		{
			mBufferID = pBufferID;

			alSourcei(mID, AL_BUFFER, mBufferID);
		}
	}

	void AudioSource::SetPosition(ALfloat pPositionX, ALfloat pPositionY)
	{
		mPositionX = pPositionX;
		mPositionY = pPositionY;

		alSource3f(mID, AL_POSITION, mPositionX, mPositionY, 0.0f);
	}

	void AudioSource::SetPosition(const Vector2& pPosition)
	{
		mPositionX = pPosition.X;
		mPositionY = pPosition.Y;

		alSource3f(mID, AL_POSITION, mPositionX, mPositionY, 0.0f);
	}

	void AudioSource::SetVelocity(ALfloat pVelocityX, ALfloat pVelocityY)
	{
		mVelocityX = pVelocityX;
		mVelocityY = pVelocityY;

		alSource3f(mID, AL_VELOCITY, mVelocityX, mVelocityY, 0.0f);
	}

	void AudioSource::SetVelocity(const Vector2& pVelocity)
	{
		mVelocityX = pVelocity.X;
		mVelocityY = pVelocity.Y;

		alSource3f(mID, AL_VELOCITY, mVelocityX, mVelocityY, 0.0f);
	}

	void AudioSource::SetPitch(ALfloat pPitch)
	{
		mPitch = pPitch;

		alSourcef(mID, AL_PITCH, mPitch);
	}

	void AudioSource::SetGain(ALfloat pGain)
	{
		mGain = pGain;

		alSourcef(mID, AL_GAIN, mGain);
	}

	void AudioSource::SetLooping(ALboolean pIsLooping)
	{
		mIsLooping = pIsLooping;

		alSourcei(mID, AL_LOOPING, mIsLooping ? AL_TRUE : AL_FALSE);
	}

	void AudioSource::Play()
	{
		alSourcePlay(mID);
	}

	void AudioSource::Pause()
	{
		alSourcePause(mID);
	}

	void AudioSource::Stop()
	{
		alSourceStop(mID);
	}
}
