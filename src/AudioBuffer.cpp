// AudioBuffer.cpp

// SDL Includes
#include <SDL2/SDL_mixer.h>
// SAGE Includes
#include <SAGE/AudioBuffer.hpp>
#include <SAGE/Console.hpp>

namespace SAGE
{
	AudioBuffer::AudioBuffer()
	{
		m_ID = 0;
	}

	AudioBuffer::~AudioBuffer()
	{
		alDeleteBuffers(1, &m_ID);
	}

	ALuint AudioBuffer::GetID() const
	{
		return m_ID;
	}

	bool AudioBuffer::Load(const std::string& p_Filename)
	{
		Mix_Chunk* chunk = Mix_LoadWAV(p_Filename.c_str());

		if (chunk == NULL)
		{
			Console::WriteLine("[AudioBuffer::Load] Failed to load audio file: %s", Mix_GetError());
			return false;
		}

		alGenBuffers(1, &m_ID);
		alBufferData(m_ID, AL_FORMAT_MONO16, chunk->abuf, chunk->alen, 44100);

		Mix_FreeChunk(chunk);

		return true;
	}
}
