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
			Vector3(float p_X, float p_Y, float p_Z);

			float Length() const;
			float LengthSquared() const;
			float Dot(const Vector3& p_Other);
			const Vector3& Normalize();
			const Vector3 Cross(const Vector3& p_Other);

			void operator()(const float p_X, const float p_Y, const float p_Z);
			bool operator==(const Vector3& p_Other) const;
			bool operator!=(const Vector3& p_Other) const;
			Vector3& operator=(const Vector3& p_Other);
			Vector3 operator-() const;
			Vector3 operator-(const Vector3& p_Other) const;
			Vector3 operator+(const Vector3& p_Other) const;
			Vector3 operator*(float p_Scalar) const;
			Vector3 operator/(float p_Scalar) const;
			Vector3& operator+=(const Vector3& p_Other);
			Vector3& operator-=(const Vector3& p_Other);
			Vector3& operator*=(float p_Scalar);
			Vector3& operator/=(float p_Scalar);

			static float Dot(const Vector3& p_VecA, const Vector3& p_VecB);
			static const Vector3 Cross(const Vector3& p_VecA, const Vector3& p_VecB);
			static float Distance(const Vector3& p_VecA, const Vector3& p_VecB);
	};
}

#endif
