// Quaternion.hpp

#ifndef __SAGE_QUATERNION_HPP__
#define __SAGE_QUATERNION_HPP__

// SAGE Includes
#include <SAGE/Matrix3.hpp>
#include <SAGE/Matrix4.hpp>

namespace SAGE
{
	class Quaternion
	{
		public:
			Quaternion();
			Quaternion(float p_Real, float p_I, float p_J, float p_K);
			Quaternion(float p_Real, const Vector3& p_Imaginary);
			Quaternion(float p_X, float p_Y, float p_Z);
			Quaternion(const Vector3& p_Angles);

			float GetReal() const;
			Vector3 GetImaginary() const;

			Quaternion& operator=(const Quaternion& p_Other);
			const Quaternion operator+(const Quaternion& p_Other) const;
			const Quaternion operator-(const Quaternion& p_Other) const;
			const Quaternion operator*(const Quaternion& p_Other) const;
			const Quaternion operator/(const Quaternion& p_Other) const;
			const Quaternion operator*(float p_Scale) const;
			const Quaternion operator/(float p_Scale) const;
			const Quaternion operator-() const;
			const Quaternion& operator+=(const Quaternion& p_Other);
			const Quaternion& operator-=(const Quaternion& p_Other);
			const Quaternion& operator*=(float p_Scale);
			const Quaternion& operator/=(float p_Scale);

			float Length() const;
			float LengthSquared() const;

			void Normalize();
			Quaternion Normalized() const;
			void Conjugate();
			void Invert();

			Quaternion Log() const;
			Quaternion Exp() const;

			Matrix3 ToMatrix3() const;
			Matrix4 ToMatrix4() const;
			void ToAxisAngle(Vector3& p_Axis, float& p_Angle) const;
			Vector3 Rotate(const Vector3& p_Rotation);
			Vector3 EulerAngles(bool p_Homogenous = true) const;

			static inline float Dot(const Quaternion& p_QuaternionA, const Quaternion& p_QuaternionB);
			static inline Quaternion FromAxisAngle(const Vector3& p_Axis, float p_Angle);
			static Quaternion Lerp(const Quaternion& p_QuaternionA, const Quaternion& p_QuaternionB, float p_T);
			static Quaternion Slerp(const Quaternion& p_QuaternionA, const Quaternion& p_QuaternionB, float p_T);
			static Quaternion SlerpNoInvert(const Quaternion& p_QuaternionA, const Quaternion& p_QuaternionB, float p_T);
			static Quaternion Squad(const Quaternion& p_Quaternion1, const Quaternion& p_Quaternion2, const Quaternion& p_QuaternionA, const Quaternion& p_QuaternionB, float p_T);
			static Quaternion Bezier(const Quaternion& p_Quaternion1, const Quaternion& p_Quaternion2, const Quaternion& p_QuaternionA, const Quaternion& p_QuaternionB, float p_T);
			static Quaternion Spline(const Quaternion& p_QuaternionM, const Quaternion& p_QuaternionN, const Quaternion& p_QuaternionP);
	
		private:
			float m_Real;
			Vector3 m_Imaginary;
	};
}

#endif
