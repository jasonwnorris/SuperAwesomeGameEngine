// Matrix3.cpp

// SAGE Includes
#include <SAGE/Matrix3.hpp>
// STL Includes
#include <utility>

namespace SAGE
{
	const Matrix3 Matrix3::Identity = Matrix3({ 1.0f, 0.0f, 0.0f,
												0.0f, 1.0f, 0.0f,
												0.0f, 0.0f, 1.0f });

	const Matrix3 Matrix3::Zero = Matrix3({ 1.0f, 0.0f, 0.0f,
											0.0f, 1.0f, 0.0f,
											0.0f, 0.0f, 1.0f });

	Matrix3::Matrix3()
	{
		Elements[0] = 1.0f;
		Elements[1] = 0.0f;
		Elements[2] = 0.0f;
		Elements[3] = 0.0f;
		Elements[4] = 1.0f;
		Elements[5] = 0.0f;
		Elements[6] = 0.0f;
		Elements[7] = 0.0f;
		Elements[8] = 1.0f;
	}

	Matrix3::Matrix3(float p_Element0, float p_Element1, float p_Element2, float p_Element3, float p_Element4, float p_Element5, float p_Element6, float p_Element7, float p_Element8)
	{
		Elements[0] = p_Element0;
		Elements[1] = p_Element1;
		Elements[2] = p_Element2;
		Elements[3] = p_Element3;
		Elements[4] = p_Element4;
		Elements[5] = p_Element5;
		Elements[6] = p_Element6;
		Elements[7] = p_Element7;
		Elements[8] = p_Element8;
	}

	Matrix3::Matrix3(const float(&M)[9])
	{
		for (int i = 0; i < 9; i++)
			Elements[i] = M[i];
	}

	Matrix3& Matrix3::operator=(const Matrix3& p_Other)
	{
		for (int i = 0; i < 9; i++)
			Elements[i] = p_Other.Elements[i];

		return *this;
	}

	Matrix3& Matrix3::operator+=(const Matrix3& p_Other)
	{
		for (int i = 0; i < 9; i++)
			Elements[i] += p_Other.Elements[i];

		return *this;
	}

	Matrix3 Matrix3::operator+(const Matrix3& p_Other) const
	{
		Matrix3 ret;

		for (int i = 0; i < 9; i++)
			ret.Elements[i] = Elements[i] + p_Other.Elements[i];

		return ret;
	}

	Matrix3& Matrix3::operator-=(const Matrix3& p_Other)
	{
		for (int i = 0; i < 9; i++)
			Elements[i] -= p_Other.Elements[i];

		return *this;
	}

	Matrix3 Matrix3::operator-(const Matrix3& p_Other) const
	{
		Matrix3 ret;

		for (int i = 0; i < 9; i++)
			ret.Elements[i] = Elements[i] - p_Other.Elements[i];

		return ret;
	}

	Matrix3& Matrix3::operator*=(const Matrix3& p_Other)
	{
		float m11 = Elements[0] * p_Other.Elements[0] + Elements[1] * p_Other.Elements[3] + Elements[2] * p_Other.Elements[6];
		float m12 = Elements[0] * p_Other.Elements[1] + Elements[1] * p_Other.Elements[4] + Elements[2] * p_Other.Elements[7];
		float m13 = Elements[0] * p_Other.Elements[2] + Elements[1] * p_Other.Elements[5] + Elements[2] * p_Other.Elements[8];
		float m21 = Elements[3] * p_Other.Elements[0] + Elements[4] * p_Other.Elements[3] + Elements[5] * p_Other.Elements[6];
		float m22 = Elements[3] * p_Other.Elements[1] + Elements[4] * p_Other.Elements[4] + Elements[5] * p_Other.Elements[7];
		float m23 = Elements[3] * p_Other.Elements[2] + Elements[4] * p_Other.Elements[5] + Elements[5] * p_Other.Elements[8];
		float m31 = Elements[6] * p_Other.Elements[0] + Elements[7] * p_Other.Elements[3] + Elements[8] * p_Other.Elements[6];
		float m32 = Elements[6] * p_Other.Elements[1] + Elements[7] * p_Other.Elements[4] + Elements[8] * p_Other.Elements[7];
		float m33 = Elements[6] * p_Other.Elements[2] + Elements[7] * p_Other.Elements[5] + Elements[8] * p_Other.Elements[8];

		Elements[0] = m11;
		Elements[1] = m12;
		Elements[2] = m13;
		Elements[3] = m21;
		Elements[4] = m22;
		Elements[5] = m23;
		Elements[6] = m31;
		Elements[7] = m32;
		Elements[8] = m33;

		return *this;
	}

	Matrix3 Matrix3::operator*(const Matrix3& p_Other) const
	{
		float m11 = Elements[0] * p_Other.Elements[0] + Elements[1] * p_Other.Elements[3] + Elements[2] * p_Other.Elements[6];
		float m12 = Elements[0] * p_Other.Elements[1] + Elements[1] * p_Other.Elements[4] + Elements[2] * p_Other.Elements[7];
		float m13 = Elements[0] * p_Other.Elements[2] + Elements[1] * p_Other.Elements[5] + Elements[2] * p_Other.Elements[8];
		float m21 = Elements[3] * p_Other.Elements[0] + Elements[4] * p_Other.Elements[3] + Elements[5] * p_Other.Elements[6];
		float m22 = Elements[3] * p_Other.Elements[1] + Elements[4] * p_Other.Elements[4] + Elements[5] * p_Other.Elements[7];
		float m23 = Elements[3] * p_Other.Elements[2] + Elements[4] * p_Other.Elements[5] + Elements[5] * p_Other.Elements[8];
		float m31 = Elements[6] * p_Other.Elements[0] + Elements[7] * p_Other.Elements[3] + Elements[8] * p_Other.Elements[6];
		float m32 = Elements[6] * p_Other.Elements[1] + Elements[7] * p_Other.Elements[4] + Elements[8] * p_Other.Elements[7];
		float m33 = Elements[6] * p_Other.Elements[2] + Elements[7] * p_Other.Elements[5] + Elements[8] * p_Other.Elements[8];

		return Matrix3(m11, m12, m13, m21, m22, m23, m31, m32, m33);
	}

	Matrix3& Matrix3::operator*=(float p_Scalar)
	{
		for (int i = 0; i < 9; i++)
			Elements[i] *= p_Scalar;

		return *this;
	}

	Matrix3 Matrix3::operator*(float p_Scalar) const
	{
		Matrix3 ret;

		for (int i = 0; i < 9; i++)
			ret.Elements[i] = Elements[i] * p_Scalar;

		return ret;
	}

	Matrix3& Matrix3::operator/=(float p_Scalar)
	{
		for (int i = 0; i < 9; i++)
			Elements[i] /= p_Scalar;

		return *this;
	}

	Matrix3 Matrix3::operator/(float p_Scalar) const
	{
		Matrix3 ret;

		for (int i = 0; i < 9; i++)
			ret.Elements[i] = Elements[i] / p_Scalar;

		return ret;
	}

	bool Matrix3::operator==(const Matrix3& p_Other) const
	{
		for (int i = 0; i < 9; i++)
			if (Elements[i] != p_Other.Elements[i])
				return false;

		return true;
	}

	bool Matrix3::operator!=(const Matrix3& p_Other) const
	{
		return !(*this == p_Other);
	}

	float Matrix3::Determinant() const
	{
		return Elements[0] * Elements[4] * Elements[8] +
			   Elements[1] * Elements[5] * Elements[6] +
			   Elements[2] * Elements[3] * Elements[7] -
			   Elements[2] * Elements[4] * Elements[6] -
			   Elements[0] * Elements[5] * Elements[7] -
			   Elements[1] * Elements[3] * Elements[8];
	}

	bool Matrix3::IsInvertable() const
	{
		return Determinant() != 0.0f;
	}

	void Matrix3::Invert()
	{
		float det = Determinant();
		if (det != 0.0)
		{
			float b11 = Elements[4] * Elements[8] - Elements[5] * Elements[7];
			float b12 = Elements[3] * Elements[8] - Elements[5] * Elements[6];
			float b13 = Elements[3] * Elements[7] - Elements[4] * Elements[6];
			float b21 = Elements[1] * Elements[8] - Elements[2] * Elements[7];
			float b22 = Elements[0] * Elements[8] - Elements[2] * Elements[6];
			float b23 = Elements[0] * Elements[7] - Elements[1] * Elements[6];
			float b31 = Elements[1] * Elements[5] - Elements[2] * Elements[4];
			float b32 = Elements[0] * Elements[5] - Elements[2] * Elements[3];
			float b33 = Elements[0] * Elements[4] - Elements[1] * Elements[3];

			Elements[0] = b11 / det;
			Elements[1] = -b21 / det;
			Elements[2] = b31 / det;
			Elements[3] = -b12 / det;
			Elements[4] = b22 / det;
			Elements[5] = -b32 / det;
			Elements[6] = b13 / det;
			Elements[7] = -b23 / det;
			Elements[8] = b33 / det;
		}
	}

	Matrix3 Matrix3::Inverse() const
	{
		float det = Determinant();
		if (det != 0.0)
		{
			float b11 = Elements[4] * Elements[8] - Elements[5] * Elements[7];
			float b12 = Elements[3] * Elements[8] - Elements[5] * Elements[6];
			float b13 = Elements[3] * Elements[7] - Elements[4] * Elements[6];
			float b21 = Elements[1] * Elements[8] - Elements[2] * Elements[7];
			float b22 = Elements[0] * Elements[8] - Elements[2] * Elements[6];
			float b23 = Elements[0] * Elements[7] - Elements[1] * Elements[6];
			float b31 = Elements[1] * Elements[5] - Elements[2] * Elements[4];
			float b32 = Elements[0] * Elements[5] - Elements[2] * Elements[3];
			float b33 = Elements[0] * Elements[4] - Elements[1] * Elements[3];

			Matrix3 ret(b11, -b21, b31, -b12, b22, -b32, b13, -b23, b33);
			ret /= det;

			return ret;
		}

		return Matrix3::Zero;
	}

	Matrix3& Matrix3::Transpose()
	{
		std::swap(Elements[1], Elements[3]);
		std::swap(Elements[2], Elements[6]);
		std::swap(Elements[5], Elements[7]);

		return *this;
	}

	Matrix3 operator*(float p_Scalar, const Matrix3& p_Matrix)
	{
		Matrix3 ret;

		for (int i = 0; i < 9; i++)
			ret.Elements[i] = p_Scalar * p_Matrix.Elements[i];

		return ret;
	}
}
