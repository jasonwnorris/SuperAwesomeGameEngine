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
	void Mouse::GetPosition(int& p_X, int& p_Y)
	{
		p_X = sCurrentX;
		p_Y = sCurrentY;
	}

	// static
	void Mouse::GetPosition(Vector2& p_Position)
	{
		p_Position.X = (float)sCurrentX;
		p_Position.Y = (float)sCurrentY;
	}

	// static
	Vector2 Mouse::GetPosition()
	{
		return Vector2(sCurrentX, sCurrentY);
	}

	// static
	void Mouse::GetMovement(int& p_X, int& p_Y)
	{
		p_X = sCurrentX - sPreviousX;
		p_Y = sCurrentY - sPreviousY;
	}

	// static
	void Mouse::GetMovement(Vector2& p_Movement)
	{
		p_Movement.X = (float)(sCurrentX - sPreviousX);
		p_Movement.Y = (float)(sCurrentY - sPreviousY);
	}

	// static
	Vector2 Mouse::GetMovement()
	{
		return Vector2(sCurrentX - sPreviousX, sCurrentY - sPreviousY);
	}

	// static
	bool Mouse::IsButtonDown(MouseButton p_Button)
	{
		return (sCurrentState & ButtonMask(p_Button)) != 0;
	}

	// static
	bool Mouse::IsButtonUp(MouseButton p_Button)
	{
		return (sCurrentState & ButtonMask(p_Button)) == 0;
	}

	// static
	bool Mouse::IsButtonClicked(MouseButton p_Button)
	{
		return (sCurrentState & ButtonMask(p_Button)) != 0 && (sPreviousState & ButtonMask(p_Button)) == 0;
	}

	// static
	bool Mouse::IsButtonReleased(MouseButton p_Button)
	{
		return (sCurrentState & ButtonMask(p_Button)) == 0 && (sPreviousState & ButtonMask(p_Button)) != 0;
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
	void Mouse::SetPosition(int p_X, int p_Y)
	{
		sCurrentX = p_X;
		sCurrentY = p_Y;
	}

	// static
	void Mouse::SetScroll(int p_X, int p_Y)
	{
		if (p_Y > 0)
		{
			sScrollUp = true;
			sScrollDown = false;
		}
		else if (p_Y < 0)
		{
			sScrollUp = false;
			sScrollDown = true;
		}
	}

	int Mouse::ButtonMask(MouseButton p_Button)
	{
		return 1 << (static_cast<int>(p_Button) - 1);
	}
}
