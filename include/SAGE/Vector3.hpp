// Vector3.hpp

#ifndef __SAGE_VECTOR3_HPP__
#define __SAGE_VECTOR3_HPP__

namespace SAGE
{
	class Vector3
	{
		public:
			static const Vector3 Up;
			static const Vector3 Down;
			static const Vector3 Left;
			static const Vector3 Right;
			static const Vector3 Forward;
			static const Vector3 Backward;
			static const Vector3 Zero;
			static const Vector3 One;

			float X;
			float Y;
			float Z;

			Vector3();
			Vector3(float pX, float pY, float pZ);

			float Length() const;
			float LengthSquared() const;
			float Dot(const Vector3& pOther);
			const Vector3& Normalize();
			const Vector3 Cross(const Vector3& pOther);

			void operator()(const float pX, const float pY, const float pZ);
			bool operator==(const Vector3& pOther) const;
			bool operator!=(const Vector3& pOther) const;
			Vector3& operator=(const Vector3& pOther);
			Vector3 operator-() const;
			Vector3 operator-(const Vector3& pOther) const;
			Vector3 operator+(const Vector3& pOther) const;
			Vector3 operator*(float pScalar) const;
			Vector3 operator/(float pScalar) const;
			Vector3& operator+=(const Vector3& pOther);
			Vector3& operator-=(const Vector3& pOther);
			Vector3& operator*=(float pScalar);
			Vector3& operator/=(float pScalar);

			static float Dot(const Vector3& pVecA, const Vector3& pVecB);
			static const Vector3 Cross(const Vector3& pVecA, const Vector3& pVecB);
			static float Distance(const Vector3& pVecA, const Vector3& pVecB);
	};
}

#endif
