// Vector3.cpp

// SAGE Includes
#include <SAGE\MathUtil.hpp>
#include <SAGE\Vector3.hpp>

namespace SAGE
{
	const Vector3 Vector3::Up = Vector3(0, 1, 0);
	const Vector3 Vector3::Down = Vector3(0, -1, 0);
	const Vector3 Vector3::Left = Vector3(-1, 0, 0);
	const Vector3 Vector3::Right = Vector3(1, 0, 0);
	const Vector3 Vector3::Forward = Vector3(0, 0, -1);
	const Vector3 Vector3::Backward = Vector3(0, 0, 1);
	const Vector3 Vector3::Zero = Vector3(0, 0, 0);
	const Vector3 Vector3::One = Vector3(1, 1, 1);

	Vector3::Vector3()
	{
		X = 0.0f;
		Y = 0.0f;
		Z = 0.0f;
	}

	Vector3::Vector3(float pX, float pY, float pZ)
	{
		X = pX;
		Y = pY;
		Z = pZ;
	}

	float Vector3::Length() const
	{
		return sqrtf(LengthSquared());
	}

	float Vector3::LengthSquared() const
	{
		return X * X + Y * Y + Z * Z;
	}

	float Vector3::Dot(const Vector3& pOther)
	{
		return X * pOther.X + Y * pOther.Y + Z * pOther.Z;
	}

	const Vector3& Vector3::Normalize()
	{
		float n = Length();
		if (n != 0.0f)
		{
			X /= n;
			Y /= n;
			Z /= n;
		}

		return *this;
	}

	const Vector3 Vector3::Cross(const Vector3& pOther)
	{
		return Vector3(Y * pOther.Z - Z * pOther.Y, Z * pOther.X - X * pOther.Z, X * pOther.Y - Y * pOther.X);
	}

	void Vector3::operator()(const float pX, const float pY, const float pZ)
	{
		X = pX;
		Y = pY;
		Z = pZ;
	}

	bool Vector3::operator==(const Vector3& pOther) const
	{
		return X == pOther.X && Y == pOther.Y && Z == pOther.Z;
	}

	bool Vector3::operator!=(const Vector3& pOther) const
	{
		return X != pOther.X || Y != pOther.Y || Z != pOther.Z;
	}

	Vector3& Vector3::operator=(const Vector3& pOther)
	{
		X = pOther.X;
		Y = pOther.Y;
		Z = pOther.Z;

		return *this;
	}

	Vector3 Vector3::operator-() const
	{
		return Vector3(-X, -Y, -Z);
	}

	Vector3 Vector3::operator-(const Vector3& pOther) const
	{
		return Vector3(X - pOther.X, Y - pOther.Y, Z - pOther.Z);
	}

	Vector3 Vector3::operator+(const Vector3& pOther) const
	{
		return Vector3(X + pOther.X, Y + pOther.Y, Z + pOther.Z);
	}

	Vector3 Vector3::operator*(float pScalar) const
	{
		return Vector3(X * pScalar, Y * pScalar, Z * pScalar);
	}

	Vector3 Vector3::operator/(float pScalar) const
	{
		return Vector3(X / pScalar, Y / pScalar, Z / pScalar);
	}

	Vector3& Vector3::operator+=(const Vector3& pOther)
	{
		X += pOther.X;
		Y += pOther.Y;
		Z += pOther.Z;

		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& pOther)
	{
		X -= pOther.X;
		Y -= pOther.Y;
		Z -= pOther.Z;

		return *this;
	}

	Vector3& Vector3::operator*=(float pScalar)
	{
		X *= pScalar;
		Y *= pScalar;
		Z *= pScalar;

		return *this;
	}

	Vector3& Vector3::operator/=(float pScalar)
	{
		X /= pScalar;
		Y /= pScalar;
		Z /= pScalar;

		return *this;
	}

	// static
	float Vector3::Dot(const Vector3& pVecA, const Vector3& pVecB)
	{
		return pVecA.X * pVecB.X + pVecA.Y * pVecB.Y + pVecA.Z * pVecB.Z;
	}

	// static 
	const Vector3 Vector3::Cross(const Vector3& pVecA, const Vector3& pVecB)
	{
		return Vector3(pVecA.Y * pVecB.Z - pVecA.Z * pVecB.Y, pVecA.Z * pVecB.X - pVecA.X * pVecB.Z, pVecA.X * pVecB.Y - pVecA.Y * pVecB.X);
	}

	// static
	float Vector3::Distance(const Vector3& pVecA, const Vector3& pVecB)
	{
		return (pVecA - pVecB).Length();
	}
}
