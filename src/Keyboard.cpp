// Keyboard.cpp

// SAGE Includes
#include <SAGE/Keyboard.hpp>

namespace SAGE
{
	std::map<Key, bool> Keyboard::sCurrentKeys;
	std::map<Key, bool> Keyboard::sPreviousKeys;

	bool Keyboard::IsKeyDown(Key p_Key)
	{
		return sCurrentKeys[p_Key];
	}

	bool Keyboard::IsKeyUp(Key p_Key)
	{
		return !sCurrentKeys[p_Key];
	}

	bool Keyboard::IsKeyPressed(Key p_Key)
	{
		return sCurrentKeys[p_Key] && !sPreviousKeys[p_Key];
	}

	bool Keyboard::IsKeyReleased(Key p_Key)
	{
		return !sCurrentKeys[p_Key] && sPreviousKeys[p_Key];
	}

	// static
	void Keyboard::Clear()
	{
		sPreviousKeys = sCurrentKeys;
	}

	// static
	void Keyboard::SetKey(Key p_Key, bool p_State)
	{
		sCurrentKeys[p_Key] = p_State;
	}
}
