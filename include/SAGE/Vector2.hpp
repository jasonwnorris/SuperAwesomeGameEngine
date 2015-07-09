// Vector2.hpp

#ifndef __SAGE_VECTOR2_HPP__
#define __SAGE_VECTOR2_HPP__

namespace SAGE
{
	class Vector2
	{
		public:
			static const Vector2 Up;
			static const Vector2 Down;
			static const Vector2 Left;
			static const Vector2 Right;
			static const Vector2 Zero;
			static const Vector2 One;

			float X;
			float Y;

			Vector2();
			Vector2(float p_X, float p_Y);
			Vector2(int p_X, int p_Y);

			float Length() const;
			float LengthSquared() const;
			float Dot(const Vector2& p_Other);
			const Vector2& Normalize();

			void operator()(const float p_X, const float p_Y);
			bool operator==(const Vector2& p_Other) const;
			bool operator!=(const Vector2& p_Other) const;
			Vector2& operator=(const Vector2& p_Other);
			Vector2 operator-() const;
			Vector2 operator-(const Vector2& p_Other) const;
			Vector2 operator+(const Vector2& p_Other) const;
			Vector2 operator*(float p_Scalar) const;
			Vector2 operator/(float p_Scalar) const;
			Vector2& operator+=(const Vector2& p_Other);
			Vector2& operator-=(const Vector2& p_Other);
			Vector2& operator*=(float p_Scalar);
			Vector2& operator/=(float p_Scalar);

			static float Length(const Vector2& p_Vector);
			static float LengthSquared(const Vector2& p_Vector);
			static float Dot(const Vector2& p_VecA, const Vector2& p_VecB);
			static float Distance(const Vector2& p_VecA, const Vector2& p_VecB);
	};
}

#endif
