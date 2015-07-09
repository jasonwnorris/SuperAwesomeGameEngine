// Matrix4.hpp

#ifndef __SAGE_MATRIX4_HPP__
#define __SAGE_MATRIX4_HPP__

// SAGE Includes
#include <SAGE\Vector3.hpp>

namespace SAGE
{
	class Matrix4
	{
		public:
			static const Matrix4 Identity;
			static const Matrix4 Zero;

			float Elements[16];

			Matrix4();
			Matrix4(float pElement0, float pElement1, float pElement2, float pElement3, float pElement4, float pElement5, float pElement6, float pElement7, float pElement8, float pElement9, float pElement10, float pElement11, float pElement12, float pElement13, float pElement14, float pElement15);
			Matrix4(const float(&M)[16]);

			void operator()(const float(&M)[16]);
			float operator()(const int pRow, const int pColumn);
			const Matrix4& operator=(const Matrix4& M);
			bool operator==(const Matrix4& M) const;
			bool operator!=(const Matrix4& M) const;
			const Matrix4 operator*(const Matrix4& M) const;
			const Matrix4& operator*=(const Matrix4& M);
			const Vector3 operator*(const Vector3& pVector);

			void Translate(const float pX, const float pY, const float pZ);
			void Translate(const Vector3& pVector);
			void Rotate(const float pX, const float pY, const float pZ);
			void Rotate(const float pAngle, const Vector3& pAxis);
			void RotateX(const float pAngle);
			void RotateY(const float pAngle);
			void RotateZ(const float pAngle);
			void Scale(const float pX, const float pY, const float pZ);
			void Scale(const float pScalar);
			void Scale(const Vector3& pVector);
			float Determinant();
			void Invert();

			static Matrix4 FromTranslation(float pX, float pY, float pZ);
			static Matrix4 FromPitchYawRoll(float pPitch, float pYaw, float pRoll);
			static Matrix4 FromScale(float pX, float pY, float pZ);
			static bool Inverse(const Matrix4& pIn, Matrix4& pOut);
	};
}

#endif
