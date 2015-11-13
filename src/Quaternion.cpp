// Quaternion.cpp

// SAGE Includes
#include <SAGE/Quaternion.hpp>
// STL Includes
#include <math.h>

namespace SAGE
{
	Quaternion::Quaternion()
	{
		m_Real = 0.0f;
		m_Imaginary = Vector3::Zero;
	}

	Quaternion::Quaternion(float p_Real, float p_I, float p_J, float p_K)
	{
		m_Real = p_Real;
		m_Imaginary = Vector3(p_I, p_J, p_K);
	}

	Quaternion::Quaternion(float p_Real, const Vector3& p_Imaginary)
	{
		m_Real = p_Real;
		m_Imaginary = p_Imaginary;
	}

	Quaternion::Quaternion(float p_X, float p_Y, float p_Z)
	{
		float cosHalfX = cosf(p_X * 0.5f);
		float cosHalfY = cosf(p_Y * 0.5f);
		float cosHalfZ = cosf(p_Z * 0.5f);

		float sinHalfX = sinf(p_X * 0.5f);
		float sinHalfY = sinf(p_Y * 0.5f);
		float sinHalfZ = sinf(p_Z * 0.5f);

		m_Real = cosHalfZ * cosHalfY * cosHalfX + sinHalfZ * sinHalfY * sinHalfX;
		m_Imaginary.X = cosHalfZ * cosHalfY * sinHalfX - sinHalfZ * sinHalfY * cosHalfX;
		m_Imaginary.Y = cosHalfZ * sinHalfY * cosHalfX + sinHalfZ * cosHalfY * sinHalfX;
		m_Imaginary.Z = sinHalfZ * cosHalfY * cosHalfX - cosHalfZ * sinHalfY * sinHalfX;
	}

	Quaternion::Quaternion(const Vector3& p_Angles)
	{
		float cosHalfX = cosf(p_Angles.X * 0.5f);
		float cosHalfY = cosf(p_Angles.Y * 0.5f);
		float cosHalfZ = cosf(p_Angles.Z * 0.5f);

		float sinHalfX = sinf(p_Angles.X * 0.5f);
		float sinHalfY = sinf(p_Angles.Y * 0.5f);
		float sinHalfZ = sinf(p_Angles.Z * 0.5f);

		m_Real = cosHalfZ * cosHalfY * cosHalfX + sinHalfZ * sinHalfY * sinHalfX;
		m_Imaginary.X = cosHalfZ * cosHalfY * sinHalfX - sinHalfZ * sinHalfY * cosHalfX;
		m_Imaginary.Y = cosHalfZ * sinHalfY * cosHalfX + sinHalfZ * cosHalfY * sinHalfX;
		m_Imaginary.Z = sinHalfZ * cosHalfY * cosHalfX - cosHalfZ * sinHalfY * sinHalfX;
	}

	float Quaternion::GetReal() const
	{
		return m_Real;
	}

	Vector3 Quaternion::GetImaginary() const
	{
		return m_Imaginary;
	}

	Quaternion& Quaternion::operator=(const Quaternion& p_Other)
	{
		m_Real = p_Other.GetReal();
		m_Imaginary = p_Other.GetImaginary();

		return *this;
	}

	const Quaternion Quaternion::operator+(const Quaternion& p_Other) const
	{
		return Quaternion(m_Real + p_Other.GetReal(), m_Imaginary + p_Other.GetImaginary());
	}

	const Quaternion Quaternion::operator-(const Quaternion& p_Other) const
	{
		return Quaternion(m_Real - p_Other.GetReal(), m_Imaginary - p_Other.GetImaginary());
	}

	const Quaternion Quaternion::operator*(const Quaternion& p_Other) const
	{
		return Quaternion(m_Real * p_Other.GetReal() - Vector3::Dot(m_Imaginary, p_Other.GetImaginary()),
			              m_Imaginary.Y * p_Other.GetImaginary().Z - m_Imaginary.Z * p_Other.GetImaginary().Y + m_Real * p_Other.GetImaginary().X + m_Imaginary.X * p_Other.GetReal(),
			              m_Imaginary.Z * p_Other.GetImaginary().X - m_Imaginary.X * p_Other.GetImaginary().Z + m_Real * p_Other.GetImaginary().Y + m_Imaginary.Y * p_Other.GetReal(),
			              m_Imaginary.X * p_Other.GetImaginary().Y - m_Imaginary.Y * p_Other.GetImaginary().X + m_Real * p_Other.GetImaginary().Z + m_Imaginary.Z * p_Other.GetReal());
	}

	const Quaternion Quaternion::operator/(const Quaternion& p_Other) const
	{
		Quaternion temp(p_Other);
		temp.Invert();

		return *this * temp;
	}

	const Quaternion Quaternion::operator*(float p_Scale) const
	{
		return Quaternion(m_Real * p_Scale, m_Imaginary * p_Scale);
	}

	const Quaternion Quaternion::operator/(float p_Scale) const
	{
		return Quaternion(m_Real / p_Scale, m_Imaginary / p_Scale);
	}

	const Quaternion Quaternion::operator-() const
	{
		return Quaternion(-m_Real, -m_Imaginary);
	}

	const Quaternion& Quaternion::operator+=(const Quaternion& p_Other)
	{
		m_Real += p_Other.GetReal();
		m_Imaginary += p_Other.GetImaginary();

		return *this;
	}

	const Quaternion& Quaternion::operator-=(const Quaternion& p_Other)
	{
		m_Real -= p_Other.GetReal();
		m_Imaginary -= p_Other.GetImaginary();

		return *this;
	}

	const Quaternion& Quaternion::operator*=(float p_Scale)
	{
		m_Real *= p_Scale;
		m_Imaginary *= p_Scale;

		return *this;
	}

	const Quaternion& Quaternion::operator/=(float p_Scale)
	{
		m_Real /= p_Scale;
		m_Imaginary /= p_Scale;

		return *this;
	}

	float Quaternion::Length() const
	{
		return sqrtf(LengthSquared());
	}

	float Quaternion::LengthSquared() const
	{
		return m_Real * m_Real + Vector3::Dot(m_Imaginary, m_Imaginary);
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
		m_Imaginary = -m_Imaginary;
	}

	void Quaternion::Invert()
	{
		Conjugate();
		*this /= LengthSquared();
	}

	Quaternion Quaternion::Log() const
	{
		float acosR = acosf(m_Real);
		float sinA = sinf(acosR);

		Vector3 ret;

		if (sinA > 0.0f)
		{
			ret.X = acosR * m_Imaginary.X / sinA;
			ret.Y = acosR * m_Imaginary.Y / sinA;
			ret.Z = acosR * m_Imaginary.Z / sinA;
		}

		return Quaternion(0, ret);
	}

	Quaternion Quaternion::Exp() const
	{
		float iLen = m_Imaginary.Length();
		float cosL = cosf(iLen);
		float sinL = sinf(iLen);

		Vector3 ret;

		if (iLen > 0.0f)
		{
			ret.X = sinL * m_Imaginary.X / iLen;
			ret.Y = sinL * m_Imaginary.Y / iLen;
			ret.Z = sinL * m_Imaginary.Z / iLen;
		}

		return Quaternion(cosL, ret);
	}

	Matrix3 Quaternion::ToMatrix3() const
	{
		float m[9] = {
			1.0f - 2.0f * (m_Imaginary.Y * m_Imaginary.Y + m_Imaginary.Z * m_Imaginary.Z), 2.0f * (m_Imaginary.X * m_Imaginary.Y - m_Real * m_Imaginary.Z), 2.0f * (m_Imaginary.X * m_Imaginary.Z + m_Real * m_Imaginary.Y),
			2.0f * (m_Imaginary.X * m_Imaginary.Y + m_Real * m_Imaginary.Z), 1.0f - 2.0f * (m_Imaginary.X * m_Imaginary.X + m_Imaginary.Z * m_Imaginary.Z), 2.0f * (m_Imaginary.Y * m_Imaginary.Z - m_Real * m_Imaginary.X),
			2.0f * (m_Imaginary.X * m_Imaginary.Z - m_Real * m_Imaginary.Y), 2.0f * (m_Imaginary.Y * m_Imaginary.Z + m_Real * m_Imaginary.X), 1.0f - 2.0f * (m_Imaginary.X * m_Imaginary.X + m_Imaginary.Y * m_Imaginary.Y)
		};

		return Matrix3(m);
	}

	Matrix4 Quaternion::ToMatrix4() const
	{
		float m[16] = {
			m_Real,        -m_Imaginary.X, -m_Imaginary.Y, -m_Imaginary.Z,
			m_Imaginary.X, m_Real,         -m_Imaginary.Z, m_Imaginary.Y,
			m_Imaginary.Y, m_Imaginary.Z,  m_Real,         -m_Imaginary.X,
			m_Imaginary.Z, -m_Imaginary.Y, m_Imaginary.X,  m_Real
		};

		return Matrix4(m);
	}

	void Quaternion::ToAxisAngle(Vector3& p_Axis, float& p_Angle) const
	{
		float acosReal = acos(m_Real);
		float sinInv = 1.0f / sinf(acosReal);

		p_Angle = acosReal * 2.0f;
		p_Axis.X = m_Imaginary.X * sinInv;
		p_Axis.Y = m_Imaginary.Y * sinInv;
		p_Axis.Z = m_Imaginary.Z * sinInv;
	}

	Vector3 Quaternion::Rotate(const Vector3& p_Rotation)
	{
		Quaternion temp(0.0f, p_Rotation);
		Quaternion conj(*this);
		conj.Conjugate();

		return (*this * temp * conj).m_Imaginary;
	}

	Vector3 Quaternion::EulerAngles(bool p_Homogenous) const
	{
		float sqReal = m_Real * m_Real;
		float sqI = m_Imaginary.X * m_Imaginary.X;
		float sqJ = m_Imaginary.Y * m_Imaginary.Y;
		float sqK = m_Imaginary.Z * m_Imaginary.Z;

		Vector3 euler;

		if (p_Homogenous)
		{
			euler.X = atan2f(2.0f * (m_Imaginary.X * m_Imaginary.Y + m_Imaginary.Z * m_Real), sqI - sqJ - sqK + sqReal);
			euler.Y = asinf(-2.0f * (m_Imaginary.X * m_Imaginary.Z - m_Imaginary.Y * m_Real));
			euler.Z = atan2f(2.0f * (m_Imaginary.Y * m_Imaginary.Z + m_Imaginary.X * m_Real), -sqI - sqJ + sqK + sqReal);
		}
		else
		{
			euler.X = atan2f(2.0f * (m_Imaginary.Z * m_Imaginary.Y + m_Imaginary.X * m_Real), 1.0f - 2.0f * (sqI + sqJ));
			euler.Y = asinf(-2.0f * (m_Imaginary.X * m_Imaginary.Z - m_Imaginary.Y * m_Real));
			euler.Z = atan2f(2.0f * (m_Imaginary.X * m_Imaginary.Y + m_Imaginary.Z * m_Real), 1.0f - 2.0f * (sqJ + sqK));
		}

		return euler;
	}

	// static
	float Quaternion::Dot(const Quaternion& p_QuaternionA, const Quaternion& p_QuaternionB)
	{
		return p_QuaternionA.GetReal() * p_QuaternionB.GetReal() + Vector3::Dot(p_QuaternionA.GetImaginary(), p_QuaternionB.GetImaginary());
	}

	// static
	Quaternion Quaternion::FromAxisAngle(const Vector3& p_Axis, float p_Angle)
	{
		return Quaternion(cosf(p_Angle / 2.0f), p_Axis * sinf(p_Angle / 2.0f));
	}

	// static
	Quaternion Quaternion::Lerp(const Quaternion& p_QuaternionA, const Quaternion& p_QuaternionB, float p_T)
	{
		Quaternion ret = p_QuaternionA * (1.0f - p_T) + p_QuaternionB * p_T;
		ret.Normalize();

		return ret;
	}

	// static
	Quaternion Quaternion::Slerp(const Quaternion& p_QuaternionA, const Quaternion& p_QuaternionB, float p_T)
	{
		float dot = Quaternion::Dot(p_QuaternionA, p_QuaternionB);

		Quaternion ret;

		if (dot < 0.0f)
		{
			dot = -dot;
			ret = -p_QuaternionB;
		}
		else
		{
			ret = p_QuaternionB;
		}

		if (dot < 0.95f)
		{
			float angle = acosf(dot);

			return (p_QuaternionA * sinf(angle * (1.0f - p_T)) + ret * sinf(angle * p_T)) / sinf(angle);
		}

		return Quaternion::Lerp(p_QuaternionA, ret, p_T);
	}

	// static
	Quaternion Quaternion::SlerpNoInvert(const Quaternion& p_QuaternionA, const Quaternion& p_QuaternionB, float p_T)
	{
		float dot = Quaternion::Dot(p_QuaternionA, p_QuaternionB);

		if (dot > -0.95f && dot < 0.95f)
		{
			float angle = acosf(dot);

			return (p_QuaternionA * sinf(angle * (1.0f - p_T)) + p_QuaternionB * sinf(angle * p_T)) / sinf(angle);
		}

		return Quaternion::Lerp(p_QuaternionA, p_QuaternionB, p_T);
	}

	// static
	Quaternion Quaternion::Squad(const Quaternion& p_Quaternion1, const Quaternion& p_Quaternion2, const Quaternion& p_QuaternionA, const Quaternion& p_QuaternionB, float p_T)
	{
		Quaternion c = Quaternion::SlerpNoInvert(p_Quaternion1, p_Quaternion2, p_T);
		Quaternion d = Quaternion::SlerpNoInvert(p_QuaternionA, p_QuaternionB, p_T);

		return Quaternion::SlerpNoInvert(c, d, 2.0f * p_T * (1.0f - p_T));
	}

	// static
	Quaternion Quaternion::Bezier(const Quaternion& p_Quaternion1, const Quaternion& p_Quaternion2, const Quaternion& p_QuaternionA, const Quaternion& p_QuaternionB, float p_T)
	{
		Quaternion q1 = Quaternion::SlerpNoInvert(p_Quaternion1, p_QuaternionA, p_T);
		Quaternion q2 = Quaternion::SlerpNoInvert(p_QuaternionA, p_QuaternionB, p_T);
		Quaternion q3 = Quaternion::SlerpNoInvert(p_QuaternionB, p_Quaternion2, p_T);

		return Quaternion::SlerpNoInvert(Quaternion::SlerpNoInvert(q1, q2, p_T), Quaternion::SlerpNoInvert(q2, q3, p_T), p_T);
	}

	// static
	Quaternion Quaternion::Spline(const Quaternion& p_QuaternionM, const Quaternion& p_QuaternionN, const Quaternion& p_QuaternionP)
	{
		Quaternion q(p_QuaternionN.GetReal(), -p_QuaternionN.GetImaginary());

		return p_QuaternionN * (((q * p_QuaternionM).Log() + (q * p_QuaternionP).Log()) / -4.0f).Exp();
	}
}
