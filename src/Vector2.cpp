// Vector2.cpp

// SAGE Includes
#include <SAGE\MathUtil.hpp>
#include <SAGE\Vector2.hpp>

namespace SAGE
{
	const Vector2 Vector2::Up = Vector2(0.0f, -1.0f);
	const Vector2 Vector2::Down = Vector2(0.0f, 1.0f);
	const Vector2 Vector2::Left = Vector2(-1.0f, 0.0f);
	const Vector2 Vector2::Right = Vector2(1.0f, 0.0f);
	const Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
	const Vector2 Vector2::One = Vector2(1.0f, 1.0f);

	Vector2::Vector2()
	{
		X = 0.0f;
		Y = 0.0f;
	}

	Vector2::Vector2(float pX, float pY)
	{
		X = pX;
		Y = pY;
	}

	Vector2::Vector2(int pX, int pY)
	{
		X = (float)pX;
		Y = (float)pY;
	}

	float Vector2::Length() const
	{
		return sqrt(LengthSquared());
	}

	float Vector2::LengthSquared() const
	{
		return X * X + Y * Y;
	}

	float Vector2::Dot(const Vector2& pOther)
	{
		return X * pOther.X + Y * pOther.Y;
	}

	const Vector2& Vector2::Normalize()
	{
		float n = Length();
		if (n != 0.0f)
		{
			X /= n;
			Y /= n;
		}

		return *this;
	}

	void Vector2::operator()(const float pX, const float pY)
	{
		X = pX;
		Y = pY;
	}

	bool Vector2::operator==(const Vector2& pOther) const
	{
		return X == pOther.X && Y == pOther.Y;
	}

	bool Vector2::operator!=(const Vector2& pOther) const
	{
		return X != pOther.X || Y != pOther.Y;
	}

	Vector2& Vector2::operator=(const Vector2& pOther)
	{
		X = pOther.X;
		Y = pOther.Y;

		return *this;
	}

	Vector2 Vector2::operator-() const
	{
		return Vector2(-X, -Y);
	}

	Vector2 Vector2::operator-(const Vector2& pOther) const
	{
		return Vector2(X - pOther.X, Y - pOther.Y);
	}

	Vector2 Vector2::operator+(const Vector2& pOther) const
	{
		return Vector2(X + pOther.X, Y + pOther.Y);
	}

	Vector2 Vector2::operator*(float pScalar) const
	{
		return Vector2(X * pScalar, Y * pScalar);
	}

	Vector2 Vector2::operator/(float pScalar) const
	{
		return Vector2(X / pScalar, Y / pScalar);
	}

	Vector2& Vector2::operator+=(const Vector2& pOther)
	{
		X += pOther.X;
		Y += pOther.Y;

		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& pOther)
	{
		X -= pOther.X;
		Y -= pOther.Y;

		return *this;
	}

	Vector2& Vector2::operator*=(float pScalar)
	{
		X *= pScalar;
		Y *= pScalar;

		return *this;
	}

	Vector2& Vector2::operator/=(float pScalar)
	{
		X /= pScalar;
		Y /= pScalar;

		return *this;
	}

	// static
	float Vector2::Length(const Vector2& pVector)
	{
		return pVector.Length();
	}

	// static
	float Vector2::LengthSquared(const Vector2& pVector)
	{
		return pVector.LengthSquared();
	}

	// static
	float Vector2::Dot(const Vector2& pVecA, const Vector2& pVecB)
	{
		return pVecA.X * pVecB.X + pVecA.Y * pVecB.Y;
	}

	// static
	float Vector2::Distance(const Vector2& pVecA, const Vector2& pVecB)
	{
		return (pVecA - pVecB).Length();
	}
}
