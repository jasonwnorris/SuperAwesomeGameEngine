// AudioSource.hpp

#ifndef __SAGE_AUDIOSOURCE_HPP__
#define __SAGE_AUDIOSOURCE_HPP__

// OpenAL Includes
#include <AL\al.h>
// SAGE Includes
#include <SAGE\Vector2.hpp>

namespace SAGE
{
	class AudioSource
	{
		public:
			AudioSource();
			AudioSource(ALuint pBufferID);
			~AudioSource();

			void SetBuffer(ALuint pBufferID);
			void SetPosition(ALfloat pPositionX, ALfloat pPositionY);
			void SetPosition(const Vector2& pPosition);
			void SetVelocity(ALfloat pVelocityX, ALfloat pVelocityY);
			void SetVelocity(const Vector2& pVelocity);
			void SetPitch(ALfloat pPitch);
			void SetGain(ALfloat pGain);
			void SetLooping(ALboolean pIsLooping);

			void Play();
			void Pause();
			void Stop();

		private:
			ALuint mID;
			ALuint mBufferID;
			ALfloat mPositionX;
			ALfloat mPositionY;
			ALfloat mVelocityX;
			ALfloat mVelocityY;
			ALfloat mPitch;
			ALfloat mGain;
			ALboolean mIsLooping;
	};
}

#endif
