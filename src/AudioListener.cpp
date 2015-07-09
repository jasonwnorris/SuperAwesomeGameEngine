// AudioListener.cpp

// SAGE Includes
#include <SAGE\AudioListener.hpp>

namespace SAGE
{
	AudioListener::AudioListener()
	{
		mPositionX = 0.0f;
		mPositionY = 0.0f;
		mVelocityX = 0.0f;
		mVelocityY = 0.0f;
		ALfloat ori[] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };

		alListener3f(AL_POSITION, mPositionX, mPositionY, 0.0f);
		alListener3f(AL_VELOCITY, mVelocityX, mVelocityY, 0.0f);
		alListenerfv(AL_ORIENTATION, ori);
	}

	AudioListener::~AudioListener()
	{
	}

	void AudioListener::SetPosition(ALfloat pPositionX, ALfloat pPositionY)
	{
		mPositionX = pPositionX;
		mPositionY = pPositionY;

		alListener3f(AL_POSITION, mPositionX, mPositionY, 0.0f);
	}

	void AudioListener::SetPosition(const Vector2& pPosition)
	{
		mPositionX = pPosition.X;
		mPositionY = pPosition.Y;

		alListener3f(AL_POSITION, mPositionX, mPositionY, 0.0f);
	}

	void AudioListener::SetVelocity(ALfloat pVelocityX, ALfloat pVelocityY)
	{
		mVelocityX = pVelocityX;
		mVelocityY = pVelocityY;

		alListener3f(AL_VELOCITY, mVelocityX, mVelocityY, 0.0f);
	}

	void AudioListener::SetVelocity(const Vector2& pVelocity)
	{
		mVelocityX = pVelocity.X;
		mVelocityY = pVelocity.Y;

		alListener3f(AL_VELOCITY, mVelocityX, mVelocityY, 0.0f);
	}
}
