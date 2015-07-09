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
			Matrix4(float p_Element0, float p_Element1, float p_Element2, float p_Element3, float p_Element4, float p_Element5, float p_Element6, float p_Element7, float p_Element8, float p_Element9, float p_Element10, float p_Element11, float p_Element12, float p_Element13, float p_Element14, float p_Element15);
			Matrix4(const float(&M)[16]);

			void operator()(const float(&M)[16]);
			float operator()(const int p_Row, const int p_Column);
			const Matrix4& operator=(const Matrix4& M);
			bool operator==(const Matrix4& M) const;
			bool operator!=(const Matrix4& M) const;
			const Matrix4 operator*(const Matrix4& M) const;
			const Matrix4& operator*=(const Matrix4& M);
			const Vector3 operator*(const Vector3& p_Vector);

			void Translate(const float p_X, const float p_Y, const float p_Z);
			void Translate(const Vector3& p_Vector);
			void Rotate(const float p_X, const float p_Y, const float p_Z);
			void Rotate(const float p_Angle, const Vector3& p_Axis);
			void RotateX(const float p_Angle);
			void RotateY(const float p_Angle);
			void RotateZ(const float p_Angle);
			void Scale(const float p_X, const float p_Y, const float p_Z);
			void Scale(const float p_Scalar);
			void Scale(const Vector3& p_Vector);
			float Determinant();
			void Invert();

			static Matrix4 FromTranslation(float p_X, float p_Y, float p_Z);
			static Matrix4 FromPitchYawRoll(float p_Pitch, float p_Yaw, float p_Roll);
			static Matrix4 FromScale(float p_X, float p_Y, float p_Z);
			static bool Inverse(const Matrix4& p_In, Matrix4& p_Out);
	};
}

#endif
