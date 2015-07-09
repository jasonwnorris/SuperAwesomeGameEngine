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
			AudioSource(ALuint p_BufferID);
			~AudioSource();

			void SetBuffer(ALuint p_BufferID);
			void SetPosition(ALfloat p_PositionX, ALfloat p_PositionY);
			void SetPosition(const Vector2& p_Position);
			void SetVelocity(ALfloat p_VelocityX, ALfloat p_VelocityY);
			void SetVelocity(const Vector2& p_Velocity);
			void SetPitch(ALfloat p_Pitch);
			void SetGain(ALfloat p_Gain);
			void SetLooping(ALboolean p_IsLooping);

			void Play();
			void Pause();
			void Stop();

		private:
			ALuint m_ID;
			ALuint m_BufferID;
			ALfloat m_PositionX;
			ALfloat m_PositionY;
			ALfloat m_VelocityX;
			ALfloat m_VelocityY;
			ALfloat m_Pitch;
			ALfloat m_Gain;
			ALboolean m_IsLooping;
	};
}

#endif
