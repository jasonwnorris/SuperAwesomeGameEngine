// AudioBuffer.hpp

#ifndef __SAGE_AUDIOBUFFER_HPP__
#define __SAGE_AUDIOBUFFER_HPP__

// STD Includes
#include <string>
// OpenAL Includes
#include <AL\al.h>

namespace SAGE
{
	class AudioBuffer
	{
		public:
			AudioBuffer();
			~AudioBuffer();

			ALuint GetID() const;

			bool Load(const std::string& p_Filename);

		private:
			ALuint m_ID;
	};
}

#endif
