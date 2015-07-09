// Matrix3.hpp

#ifndef __SAGE_MATRIX3_HPP__
#define __SAGE_MATRIX3_HPP__

namespace SAGE
{
	class Matrix3
	{
		public:
			static const Matrix3 Identity;
			static const Matrix3 Zero;

			float Elements[9];

			Matrix3();
			Matrix3(float pElement0, float pElement1, float pElement2, float pElement3, float pElement4, float pElement5, float pElement6, float pElement7, float pElement8);
			Matrix3(const float(&M)[9]);

			Matrix3& operator=(const Matrix3& pOther);
			Matrix3& operator+=(const Matrix3& pOther);
			Matrix3 operator+(const Matrix3& pOther) const;
			Matrix3& operator-=(const Matrix3& pOther);
			Matrix3 operator-(const Matrix3& pOther) const;
			Matrix3& operator*=(const Matrix3& pOther);
			Matrix3 operator*(const Matrix3& pOther) const;
			Matrix3& operator*=(float pScalar);
			Matrix3 operator*(float pScalar) const;
			Matrix3& operator/=(float pScalar);
			Matrix3 operator/(float pScalar) const;
			bool operator==(const Matrix3& pOther) const;
			bool operator!=(const Matrix3& pOther) const;

			float Determinant() const;
			bool IsInvertable() const;
			void Invert();
			Matrix3 Inverse() const;
			Matrix3& Transpose();
	};

	Matrix3 operator*(float pScalar, const Matrix3& pMatrix);
}

#endif
