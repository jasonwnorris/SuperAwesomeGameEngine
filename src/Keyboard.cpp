// Keyboard.cpp

// SAGE Includes
#include <SAGE\Keyboard.hpp>

namespace SAGE
{
	std::map<Key, bool> Keyboard::sCurrentKeys;
	std::map<Key, bool> Keyboard::sPreviousKeys;

	bool Keyboard::IsKeyDown(Key pKey)
	{
		return sCurrentKeys[pKey];
	}

	bool Keyboard::IsKeyUp(Key pKey)
	{
		return !sCurrentKeys[pKey];
	}

	bool Keyboard::IsKeyPressed(Key pKey)
	{
		return sCurrentKeys[pKey] && !sPreviousKeys[pKey];
	}

	bool Keyboard::IsKeyReleased(Key pKey)
	{
		return !sCurrentKeys[pKey] && sPreviousKeys[pKey];
	}

	// static
	void Keyboard::Clear()
	{
		sPreviousKeys = sCurrentKeys;
	}

	// static
	void Keyboard::SetKey(Key pKey, bool pState)
	{
		sCurrentKeys[pKey] = pState;
	}
}
