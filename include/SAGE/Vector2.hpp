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
			Vector2(float pX, float pY);
			Vector2(int pX, int pY);

			float Length() const;
			float LengthSquared() const;
			float Dot(const Vector2& pOther);
			const Vector2& Normalize();

			void operator()(const float pX, const float pY);
			bool operator==(const Vector2& pOther) const;
			bool operator!=(const Vector2& pOther) const;
			Vector2& operator=(const Vector2& pOther);
			Vector2 operator-() const;
			Vector2 operator-(const Vector2& pOther) const;
			Vector2 operator+(const Vector2& pOther) const;
			Vector2 operator*(float pScalar) const;
			Vector2 operator/(float pScalar) const;
			Vector2& operator+=(const Vector2& pOther);
			Vector2& operator-=(const Vector2& pOther);
			Vector2& operator*=(float pScalar);
			Vector2& operator/=(float pScalar);

			static float Length(const Vector2& pVector);
			static float LengthSquared(const Vector2& pVector);
			static float Dot(const Vector2& pVecA, const Vector2& pVecB);
			static float Distance(const Vector2& pVecA, const Vector2& pVecB);
	};
}

#endif
