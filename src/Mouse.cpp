// Mouse.cpp

// SAGE Includes
#include <SAGE\Mouse.hpp>

namespace SAGE
{
	int Mouse::sPreviousX;
	int Mouse::sCurrentX;
	int Mouse::sPreviousY;
	int Mouse::sCurrentY;
	Uint32 Mouse::sPreviousState;
	Uint32 Mouse::sCurrentState;
	bool Mouse::sScrollUp;
	bool Mouse::sScrollDown;

	// static
	void Mouse::GetPosition(int& pX, int& pY)
	{
		pX = sCurrentX;
		pY = sCurrentY;
	}

	// static
	void Mouse::GetPosition(Vector2& pPosition)
	{
		pPosition.X = (float)sCurrentX;
		pPosition.Y = (float)sCurrentY;
	}

	// static
	Vector2 Mouse::GetPosition()
	{
		return Vector2(sCurrentX, sCurrentY);
	}

	// static
	void Mouse::GetMovement(int& pX, int& pY)
	{
		pX = sCurrentX - sPreviousX;
		pY = sCurrentY - sPreviousY;
	}

	// static
	void Mouse::GetMovement(Vector2& pMovement)
	{
		pMovement.X = (float)(sCurrentX - sPreviousX);
		pMovement.Y = (float)(sCurrentY - sPreviousY);
	}

	// static
	Vector2 Mouse::GetMovement()
	{
		return Vector2(sCurrentX - sPreviousX, sCurrentY - sPreviousY);
	}

	// static
	bool Mouse::IsButtonDown(MouseButton pButton)
	{
		return (sCurrentState & ButtonMask(pButton)) != 0;
	}

	// static
	bool Mouse::IsButtonUp(MouseButton pButton)
	{
		return (sCurrentState & ButtonMask(pButton)) == 0;
	}

	// static
	bool Mouse::IsButtonClicked(MouseButton pButton)
	{
		return (sCurrentState & ButtonMask(pButton)) != 0 && (sPreviousState & ButtonMask(pButton)) == 0;
	}

	// static
	bool Mouse::IsButtonReleased(MouseButton pButton)
	{
		return (sCurrentState & ButtonMask(pButton)) == 0 && (sPreviousState & ButtonMask(pButton)) != 0;
	}

	// static
	bool Mouse::IsScrolledUp()
	{
		return sScrollUp;
	}

	// static
	bool Mouse::IsScrolledDown()
	{
		return sScrollDown;
	}

	// static
	void Mouse::Clear()
	{
		sPreviousX = sCurrentX;
		sPreviousY = sCurrentY;
		sPreviousState = sCurrentState;
		sCurrentState = SDL_GetMouseState(NULL, NULL);
		sScrollUp = false;
		sScrollDown = false;
	}

	// static
	void Mouse::SetPosition(int pX, int pY)
	{
		sCurrentX = pX;
		sCurrentY = pY;
	}

	// static
	void Mouse::SetScroll(int pX, int pY)
	{
		if (pY > 0)
		{
			sScrollUp = true;
			sScrollDown = false;
		}
		else if (pY < 0)
		{
			sScrollUp = false;
			sScrollDown = true;
		}
	}

	int Mouse::ButtonMask(MouseButton pButton)
	{
		return 1 << (static_cast<int>(pButton) - 1);
	}
}
