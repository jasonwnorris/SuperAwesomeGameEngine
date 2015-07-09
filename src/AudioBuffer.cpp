// AudioBuffer.cpp

// SDL Includes
#include <SDL2\SDL_mixer.h>
// SAGE Includes
#include <SAGE\AudioBuffer.hpp>
#include <SAGE\Console.hpp>

namespace SAGE
{
	AudioBuffer::AudioBuffer()
	{
		mID = 0;
	}

	AudioBuffer::~AudioBuffer()
	{
		alDeleteBuffers(1, &mID);
	}

	ALuint AudioBuffer::GetID() const
	{
		return mID;
	}

	bool AudioBuffer::Load(const std::string& pFilename)
	{
		Mix_Chunk* chunk = Mix_LoadWAV(pFilename.c_str());

		if (chunk == NULL)
		{
			Console::WriteLine("[AudioBuffer::Load] Failed to load audio file: %s", Mix_GetError());
			return false;
		}

		alGenBuffers(1, &mID);
		alBufferData(mID, AL_FORMAT_MONO16, chunk->abuf, chunk->alen, 44100);

		Mix_FreeChunk(chunk);

		return true;
	}
}
