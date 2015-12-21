// AudioListener.hpp

#ifndef __SAGE_AUDIOLISTENER_HPP__
#define __SAGE_AUDIOLISTENER_HPP__

// OpenAL Includes
#include <AL/al.h>
// SAGE Includes
#include <SAGE/Vector2.hpp>

namespace SAGE
{
	class AudioListener
	{
		public:
			AudioListener();
			~AudioListener();

			void SetPosition(ALfloat p_PositionX, ALfloat p_PositionY);
			void SetPosition(const Vector2& p_Position);
			void SetVelocity(ALfloat p_PositionX, ALfloat p_PositionY);
			void SetVelocity(const Vector2& p_Velocity);

		private:
			ALfloat m_PositionX;
			ALfloat m_PositionY;
			ALfloat m_VelocityX;
			ALfloat m_VelocityY;
	};
}

#endif
