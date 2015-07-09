// Quaternion.cpp

// SAGE Includes
#include <SAGE\Quaternion.hpp>
// STL Includes
#include <math.h>

namespace SAGE
{
	Quaternion::Quaternion()
	{
		mReal = 0.0f;
		mImaginary = Vector3::Zero;
	}

	Quaternion::Quaternion(float pReal, float pI, float pJ, float pK)
	{
		mReal = pReal;
		mImaginary = Vector3(pI, pJ, pK);
	}

	Quaternion::Quaternion(float pReal, const Vector3& pImaginary)
	{
		mReal = pReal;
		mImaginary = pImaginary;
	}

	Quaternion::Quaternion(float pX, float pY, float pZ)
	{
		float cosHalfX = cosf(pX * 0.5f);
		float cosHalfY = cosf(pY * 0.5f);
		float cosHalfZ = cosf(pZ * 0.5f);

		float sinHalfX = sinf(pX * 0.5f);
		float sinHalfY = sinf(pY * 0.5f);
		float sinHalfZ = sinf(pZ * 0.5f);

		mReal = cosHalfZ * cosHalfY * cosHalfX + sinHalfZ * sinHalfY * sinHalfX;
		mImaginary.X = cosHalfZ * cosHalfY * sinHalfX - sinHalfZ * sinHalfY * cosHalfX;
		mImaginary.Y = cosHalfZ * sinHalfY * cosHalfX + sinHalfZ * cosHalfY * sinHalfX;
		mImaginary.Z = sinHalfZ * cosHalfY * cosHalfX - cosHalfZ * sinHalfY * sinHalfX;
	}

	Quaternion::Quaternion(const Vector3& pAngles)
	{
		float cosHalfX = cosf(pAngles.X * 0.5f);
		float cosHalfY = cosf(pAngles.Y * 0.5f);
		float cosHalfZ = cosf(pAngles.Z * 0.5f);

		float sinHalfX = sinf(pAngles.X * 0.5f);
		float sinHalfY = sinf(pAngles.Y * 0.5f);
		float sinHalfZ = sinf(pAngles.Z * 0.5f);

		mReal = cosHalfZ * cosHalfY * cosHalfX + sinHalfZ * sinHalfY * sinHalfX;
		mImaginary.X = cosHalfZ * cosHalfY * sinHalfX - sinHalfZ * sinHalfY * cosHalfX;
		mImaginary.Y = cosHalfZ * sinHalfY * cosHalfX + sinHalfZ * cosHalfY * sinHalfX;
		mImaginary.Z = sinHalfZ * cosHalfY * cosHalfX - cosHalfZ * sinHalfY * sinHalfX;
	}

	float Quaternion::GetReal() const
	{
		return mReal;
	}

	Vector3 Quaternion::GetImaginary() const
	{
		return mImaginary;
	}

	Quaternion& Quaternion::operator=(const Quaternion& pOther)
	{
		mReal = pOther.GetReal();
		mImaginary = pOther.GetImaginary();

		return *this;
	}

	const Quaternion Quaternion::operator+(const Quaternion& pOther) const
	{
		return Quaternion(mReal + pOther.GetReal(), mImaginary + pOther.GetImaginary());
	}

	const Quaternion Quaternion::operator-(const Quaternion& pOther) const
	{
		return Quaternion(mReal - pOther.GetReal(), mImaginary - pOther.GetImaginary());
	}

	const Quaternion Quaternion::operator*(const Quaternion& pOther) const
	{
		return Quaternion(mReal * pOther.GetReal() - Vector3::Dot(mImaginary, pOther.GetImaginary()),
			              mImaginary.Y * pOther.GetImaginary().Z - mImaginary.Z * pOther.GetImaginary().Y + mReal * pOther.GetImaginary().X + mImaginary.X * pOther.GetReal(),
			              mImaginary.Z * pOther.GetImaginary().X - mImaginary.X * pOther.GetImaginary().Z + mReal * pOther.GetImaginary().Y + mImaginary.Y * pOther.GetReal(),
			              mImaginary.X * pOther.GetImaginary().Y - mImaginary.Y * pOther.GetImaginary().X + mReal * pOther.GetImaginary().Z + mImaginary.Z * pOther.GetReal());
	}

	const Quaternion Quaternion::operator/(const Quaternion& pOther) const
	{
		Quaternion temp(pOther);
		temp.Invert();

		return *this * temp;
	}

	const Quaternion Quaternion::operator*(float pScale) const
	{
		return Quaternion(mReal * pScale, mImaginary * pScale);
	}

	const Quaternion Quaternion::operator/(float pScale) const
	{
		return Quaternion(mReal / pScale, mImaginary / pScale);
	}

	const Quaternion Quaternion::operator-() const
	{
		return Quaternion(-mReal, -mImaginary);
	}

	const Quaternion& Quaternion::operator+=(const Quaternion& pOther)
	{
		mReal += pOther.GetReal();
		mImaginary += pOther.GetImaginary();

		return *this;
	}

	const Quaternion& Quaternion::operator-=(const Quaternion& pOther)
	{
		mReal -= pOther.GetReal();
		mImaginary -= pOther.GetImaginary();

		return *this;
	}

	const Quaternion& Quaternion::operator*=(float pScale)
	{
		mReal *= pScale;
		mImaginary *= pScale;

		return *this;
	}

	const Quaternion& Quaternion::operator/=(float pScale)
	{
		mReal /= pScale;
		mImaginary /= pScale;

		return *this;
	}

	float Quaternion::Length() const
	{
		return sqrtf(LengthSquared());
	}

	float Quaternion::LengthSquared() const
	{
		return mReal * mReal + Vector3::Dot(mImaginary, mImaginary);
	}

	void Quaternion::Normalize()
	{
		*this /= Length();
	}

	Quaternion Quaternion::Normalized() const
	{
		return *this / Length();
	}

	void Quaternion::Conjugate()
	{
		mImaginary = -mImaginary;
	}

	void Quaternion::Invert()
	{
		Conjugate();
		*this /= LengthSquared();
	}

	Quaternion Quaternion::Log() const
	{
		float acosR = acosf(mReal);
		float sinA = sinf(acosR);

		Vector3 ret;

		if (sinA > 0.0f)
		{
			ret.X = acosR * mImaginary.X / sinA;
			ret.Y = acosR * mImaginary.Y / sinA;
			ret.Z = acosR * mImaginary.Z / sinA;
		}

		return Quaternion(0, ret);
	}

	Quaternion Quaternion::Exp() const
	{
		float iLen = mImaginary.Length();
		float cosL = cosf(iLen);
		float sinL = sinf(iLen);

		Vector3 ret;

		if (iLen > 0.0f)
		{
			ret.X = sinL * mImaginary.X / iLen;
			ret.Y = sinL * mImaginary.Y / iLen;
			ret.Z = sinL * mImaginary.Z / iLen;
		}

		return Quaternion(cosL, ret);
	}

	Matrix3 Quaternion::ToMatrix3() const
	{
		float m[9] = {
			1.0f - 2.0f * (mImaginary.Y * mImaginary.Y + mImaginary.Z * mImaginary.Z), 2.0f * (mImaginary.X * mImaginary.Y - mReal * mImaginary.Z), 2.0f * (mImaginary.X * mImaginary.Z + mReal * mImaginary.Y),
			2.0f * (mImaginary.X * mImaginary.Y + mReal * mImaginary.Z), 1.0f - 2.0f * (mImaginary.X * mImaginary.X + mImaginary.Z * mImaginary.Z), 2.0f * (mImaginary.Y * mImaginary.Z - mReal * mImaginary.X),
			2.0f * (mImaginary.X * mImaginary.Z - mReal * mImaginary.Y), 2.0f * (mImaginary.Y * mImaginary.Z + mReal * mImaginary.X), 1.0f - 2.0f * (mImaginary.X * mImaginary.X + mImaginary.Y * mImaginary.Y)
		};

		return Matrix3(m);
	}

	Matrix4 Quaternion::ToMatrix4() const
	{
		float m[16] = {
			mReal,        -mImaginary.X, -mImaginary.Y, -mImaginary.Z,
			mImaginary.X, mReal,         -mImaginary.Z, mImaginary.Y,
			mImaginary.Y, mImaginary.Z,  mReal,         -mImaginary.X,
			mImaginary.Z, -mImaginary.Y, mImaginary.X,  mReal
		};

		return Matrix4(m);
	}

	void Quaternion::ToAxisAngle(Vector3& pAxis, float& pAngle) const
	{
		float acosReal = acos(mReal);
		float sinInv = 1.0f / sinf(acosReal);

		pAngle = acosReal * 2.0f;
		pAxis.X = mImaginary.X * sinInv;
		pAxis.Y = mImaginary.Y * sinInv;
		pAxis.Z = mImaginary.Z * sinInv;
	}

	Vector3 Quaternion::Rotate(const Vector3& pRotation)
	{
		Quaternion temp(0.0f, pRotation);
		Quaternion conj(*this);
		conj.Conjugate();

		return (*this * temp * conj).mImaginary;
	}

	Vector3 Quaternion::EulerAngles(bool pHomogenous) const
	{
		float sqReal = mReal * mReal;
		float sqI = mImaginary.X * mImaginary.X;
		float sqJ = mImaginary.Y * mImaginary.Y;
		float sqK = mImaginary.Z * mImaginary.Z;

		Vector3 euler;

		if (pHomogenous)
		{
			euler.X = atan2f(2.0f * (mImaginary.X * mImaginary.Y + mImaginary.Z * mReal), sqI - sqJ - sqK + sqReal);
			euler.Y = asinf(-2.0f * (mImaginary.X * mImaginary.Z - mImaginary.Y * mReal));
			euler.Z = atan2f(2.0f * (mImaginary.Y * mImaginary.Z + mImaginary.X * mReal), -sqI - sqJ + sqK + sqReal);
		}
		else
		{
			euler.X = atan2f(2.0f * (mImaginary.Z * mImaginary.Y + mImaginary.X * mReal), 1.0f - 2.0f * (sqI + sqJ));
			euler.Y = asinf(-2.0f * (mImaginary.X * mImaginary.Z - mImaginary.Y * mReal));
			euler.Z = atan2f(2.0f * (mImaginary.X * mImaginary.Y + mImaginary.Z * mReal), 1.0f - 2.0f * (sqJ + sqK));
		}

		return euler;
	}

	// static
	float Quaternion::Dot(const Quaternion& pQuaternionA, const Quaternion& pQuaternionB)
	{
		return pQuaternionA.GetReal() * pQuaternionB.GetReal() + Vector3::Dot(pQuaternionA.GetImaginary(), pQuaternionB.GetImaginary());
	}

	// static
	Quaternion Quaternion::FromAxisAngle(const Vector3& pAxis, float pAngle)
	{
		return Quaternion(cosf(pAngle / 2.0f), pAxis * sinf(pAngle / 2.0f));
	}

	// static
	Quaternion Quaternion::Lerp(const Quaternion& pQuaternionA, const Quaternion& pQuaternionB, float pT)
	{
		Quaternion ret = pQuaternionA * (1.0f - pT) + pQuaternionB * pT;
		ret.Normalize();

		return ret;
	}

	// static
	Quaternion Quaternion::Slerp(const Quaternion& pQuaternionA, const Quaternion& pQuaternionB, float pT)
	{
		float dot = Quaternion::Dot(pQuaternionA, pQuaternionB);

		Quaternion ret;

		if (dot < 0.0f)
		{
			dot = -dot;
			ret = -pQuaternionB;
		}
		else
		{
			ret = pQuaternionB;
		}

		if (dot < 0.95f)
		{
			float angle = acosf(dot);

			return (pQuaternionA * sinf(angle * (1.0f - pT)) + ret * sinf(angle * pT)) / sinf(angle);
		}

		return Quaternion::Lerp(pQuaternionA, ret, pT);
	}

	// static
	Quaternion Quaternion::SlerpNoInvert(const Quaternion& pQuaternionA, const Quaternion& pQuaternionB, float pT)
	{
		float dot = Quaternion::Dot(pQuaternionA, pQuaternionB);

		if (dot > -0.95f && dot < 0.95f)
		{
			float angle = acosf(dot);

			return (pQuaternionA * sinf(angle * (1.0f - pT)) + pQuaternionB * sinf(angle * pT)) / sinf(angle);
		}

		return Quaternion::Lerp(pQuaternionA, pQuaternionB, pT);
	}

	// static
	Quaternion Quaternion::Squad(const Quaternion& pQuaternion1, const Quaternion& pQuaternion2, const Quaternion& pQuaternionA, const Quaternion& pQuaternionB, float pT)
	{
		Quaternion c = Quaternion::SlerpNoInvert(pQuaternion1, pQuaternion2, pT);
		Quaternion d = Quaternion::SlerpNoInvert(pQuaternionA, pQuaternionB, pT);

		return Quaternion::SlerpNoInvert(c, d, 2.0f * pT * (1.0f - pT));
	}

	// static
	Quaternion Quaternion::Bezier(const Quaternion& pQuaternion1, const Quaternion& pQuaternion2, const Quaternion& pQuaternionA, const Quaternion& pQuaternionB, float pT)
	{
		Quaternion q1 = Quaternion::SlerpNoInvert(pQuaternion1, pQuaternionA, pT);
		Quaternion q2 = Quaternion::SlerpNoInvert(pQuaternionA, pQuaternionB, pT);
		Quaternion q3 = Quaternion::SlerpNoInvert(pQuaternionB, pQuaternion2, pT);

		return Quaternion::SlerpNoInvert(Quaternion::SlerpNoInvert(q1, q2, pT), Quaternion::SlerpNoInvert(q2, q3, pT), pT);
	}

	// static
	Quaternion Quaternion::Spline(const Quaternion& pQuaternionM, const Quaternion& pQuaternionN, const Quaternion& pQuaternionP)
	{
		Quaternion q(pQuaternionN.GetReal(), -pQuaternionN.GetImaginary());

		return pQuaternionN * (((q * pQuaternionM).Log() + (q * pQuaternionP).Log()) / -4.0f).Exp();
	}
}
