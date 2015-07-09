// Quaternion.hpp

#ifndef __SAGE_QUATERNION_HPP__
#define __SAGE_QUATERNION_HPP__

// SAGE Includes
#include <SAGE\Matrix3.hpp>
#include <SAGE\Matrix4.hpp>

namespace SAGE
{
	class Quaternion
	{
		public:
			Quaternion();
			Quaternion(float pReal, float pI, float pJ, float pK);
			Quaternion(float pReal, const Vector3& pImaginary);
			Quaternion(float pX, float pY, float pZ);
			Quaternion(const Vector3& pAngles);

			float GetReal() const;
			Vector3 GetImaginary() const;

			Quaternion& operator=(const Quaternion& pOther);
			const Quaternion operator+(const Quaternion& pOther) const;
			const Quaternion operator-(const Quaternion& pOther) const;
			const Quaternion operator*(const Quaternion& pOther) const;
			const Quaternion operator/(const Quaternion& pOther) const;
			const Quaternion operator*(float pScale) const;
			const Quaternion operator/(float pScale) const;
			const Quaternion operator-() const;
			const Quaternion& operator+=(const Quaternion& pOther);
			const Quaternion& operator-=(const Quaternion& pOther);
			const Quaternion& operator*=(float pScale);
			const Quaternion& operator/=(float pScale);

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
			void ToAxisAngle(Vector3& pAxis, float& pAngle) const;
			Vector3 Rotate(const Vector3& pRotation);
			Vector3 EulerAngles(bool pHomogenous = true) const;

			static inline float Dot(const Quaternion& pQuaternionA, const Quaternion& pQuaternionB);
			static inline Quaternion FromAxisAngle(const Vector3& pAxis, float pAngle);
			static Quaternion Lerp(const Quaternion& pQuaternionA, const Quaternion& pQuaternionB, float pT);
			static Quaternion Slerp(const Quaternion& pQuaternionA, const Quaternion& pQuaternionB, float pT);
			static Quaternion SlerpNoInvert(const Quaternion& pQuaternionA, const Quaternion& pQuaternionB, float pT);
			static Quaternion Squad(const Quaternion& pQuaternion1, const Quaternion& pQuaternion2, const Quaternion& pQuaternionA, const Quaternion& pQuaternionB, float pT);
			static Quaternion Bezier(const Quaternion& pQuaternion1, const Quaternion& pQuaternion2, const Quaternion& pQuaternionA, const Quaternion& pQuaternionB, float pT);
			static Quaternion Spline(const Quaternion& pQuaternionM, const Quaternion& pQuaternionN, const Quaternion& pQuaternionP);
	
		private:
			float mReal;
			Vector3 mImaginary;
	};
}

#endif
