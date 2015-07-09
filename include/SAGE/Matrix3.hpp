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
			Matrix3(float p_Element0, float p_Element1, float p_Element2, float p_Element3, float p_Element4, float p_Element5, float p_Element6, float p_Element7, float p_Element8);
			Matrix3(const float(&M)[9]);

			Matrix3& operator=(const Matrix3& p_Other);
			Matrix3& operator+=(const Matrix3& p_Other);
			Matrix3 operator+(const Matrix3& p_Other) const;
			Matrix3& operator-=(const Matrix3& p_Other);
			Matrix3 operator-(const Matrix3& p_Other) const;
			Matrix3& operator*=(const Matrix3& p_Other);
			Matrix3 operator*(const Matrix3& p_Other) const;
			Matrix3& operator*=(float p_Scalar);
			Matrix3 operator*(float p_Scalar) const;
			Matrix3& operator/=(float p_Scalar);
			Matrix3 operator/(float p_Scalar) const;
			bool operator==(const Matrix3& p_Other) const;
			bool operator!=(const Matrix3& p_Other) const;

			float Determinant() const;
			bool IsInvertable() const;
			void Invert();
			Matrix3 Inverse() const;
			Matrix3& Transpose();
	};

	Matrix3 operator*(float p_Scalar, const Matrix3& p_Matrix);
}

#endif
