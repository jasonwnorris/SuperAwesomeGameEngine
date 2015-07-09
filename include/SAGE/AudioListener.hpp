// AudioListener.hpp

#ifndef __SAGE_AUDIOLISTENER_HPP__
#define __SAGE_AUDIOLISTENER_HPP__

// OpenAL Includes
#include <AL\al.h>
// SAGE Includes
#include <SAGE\Vector2.hpp>

namespace SAGE
{
	class AudioListener
	{
		public:
			AudioListener();
			~AudioListener();

			void SetPosition(ALfloat pPositionX, ALfloat pPositionY);
			void SetPosition(const Vector2& pPosition);
			void SetVelocity(ALfloat pPositionX, ALfloat pPositionY);
			void SetVelocity(const Vector2& pVelocity);

		private:
			ALfloat mPositionX;
			ALfloat mPositionY;
			ALfloat mVelocityX;
			ALfloat mVelocityY;
	};
}

#endif
