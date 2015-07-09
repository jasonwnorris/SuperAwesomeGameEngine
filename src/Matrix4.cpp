// Matrix4.cpp

// SAGE Includes
#include <SAGE\Matrix4.hpp>
// STL Includes
#include <math.h>

namespace SAGE
{
	const Matrix4 Matrix4::Identity = Matrix4({ 1.0f, 0.0f, 0.0f, 0.0f,
												0.0f, 1.0f, 0.0f, 0.0f,
												0.0f, 0.0f, 1.0f, 0.0f,
												0.0f, 0.0f, 0.0f, 1.0f });
	
	const Matrix4 Matrix4::Zero = Matrix4({ 0.0f, 0.0f, 0.0f, 0.0f,
											0.0f, 0.0f, 0.0f, 0.0f,
											0.0f, 0.0f, 0.0f, 0.0f,
											0.0f, 0.0f, 0.0f, 0.0f });

	Matrix4::Matrix4()
	{
		Elements[0] = 1.0f;
		Elements[1] = 0.0f;
		Elements[2] = 0.0f;
		Elements[3] = 0.0f;
		Elements[4] = 0.0f;
		Elements[5] = 1.0f;
		Elements[6] = 0.0f;
		Elements[7] = 0.0f;
		Elements[8] = 0.0f;
		Elements[9] = 0.0f;
		Elements[10] = 1.0f;
		Elements[11] = 0.0f;
		Elements[12] = 0.0f;
		Elements[13] = 0.0f;
		Elements[14] = 0.0f;
		Elements[15] = 1.0f;
	}

	Matrix4::Matrix4(float pElement0, float pElement1, float pElement2, float pElement3, float pElement4, float pElement5, float pElement6, float pElement7, float pElement8, float pElement9, float pElement10, float pElement11, float pElement12, float pElement13, float pElement14, float pElement15)
	{
		Elements[0] = pElement0;
		Elements[1] = pElement1;
		Elements[2] = pElement2;
		Elements[3] = pElement3;
		Elements[4] = pElement4;
		Elements[5] = pElement5;
		Elements[6] = pElement6;
		Elements[7] = pElement7;
		Elements[8] = pElement8;
		Elements[9] = pElement9;
		Elements[10] = pElement10;
		Elements[11] = pElement11;
		Elements[12] = pElement12;
		Elements[13] = pElement13;
		Elements[14] = pElement14;
		Elements[15] = pElement15;
	}

	Matrix4::Matrix4(const float(&M)[16])
	{
		for (int i = 0; i < 16; i++)
			Elements[i] = M[i];
	}

	void Matrix4::operator()(const float(&M)[16])
	{
		for (int i = 0; i < 16; i++)
			Elements[i] = M[i];
	}

	float Matrix4::operator()(const int pRow, const int pColumn)
	{
		return Elements[(pRow * 4) + pColumn];
	}

	const Matrix4& Matrix4::operator=(const Matrix4& M)
	{
		for (int i = 0; i < 16; i++)
			Elements[i] = M.Elements[i];

		return *this;
	}

	bool Matrix4::operator==(const Matrix4& M) const
	{
		for (int i = 0; i < 16; i++)
		if (Elements[i] != M.Elements[i])
			return false;

		return true;
	}

	bool Matrix4::operator!=(const Matrix4& M) const
	{
		return !(*this == M);
	}

	const Matrix4 Matrix4::operator*(const Matrix4& M) const
	{
		Matrix4 result;

		for (int col = 0; col < 4; col++)
		for (int row = 0; row < 4; row++)
			result.Elements[(row * 4) + col] = Elements[col] * M.Elements[row * 4] +
			Elements[col + 4] * M.Elements[1 + (row * 4)] +
			Elements[col + 8] * M.Elements[2 + (row * 4)] +
			Elements[col + 12] * M.Elements[3 + (row * 4)];

		return result;
	}

	const Matrix4& Matrix4::operator*=(const Matrix4& M)
	{
		(*this) = (*this) * M;

		return *this;
	}

	const Vector3 Matrix4::operator*(const Vector3& pVector)
	{
		return Vector3(pVector.X * Elements[0] + pVector.Y * Elements[1] + pVector.Z * Elements[2] + Elements[3],
			pVector.X * Elements[4] + pVector.Y * Elements[5] + pVector.Z * Elements[6] + Elements[7],
			pVector.X * Elements[8] + pVector.Y * Elements[9] + pVector.Z * Elements[10] + Elements[11]);
	}

	void Matrix4::Translate(const float pX, const float pY, const float pZ)
	{
		Elements[3] += pX;
		Elements[7] += pY;
		Elements[11] += pZ;
	}

	void Matrix4::Translate(const Vector3& pVector)
	{
		Translate(pVector.X, pVector.Y, pVector.Z);
	}

	void Matrix4::Rotate(const float pX, const float pY, const float pZ)
	{
		Matrix4 _matrixX;
		_matrixX.RotateX(pX);
		(*this) *= _matrixX;

		Matrix4 _matrixY;
		_matrixY.RotateY(pY);
		(*this) *= _matrixY;

		Matrix4 _matrixZ;
		_matrixZ.RotateZ(pZ);
		(*this) *= _matrixZ;
	}

	void Matrix4::Rotate(const float pAngle, const Vector3& pAxis)
	{
		float sinTheta = sinf(pAngle);
		float cosTheta = cosf(pAngle);
		float tanTheta = 1.0f - cosTheta;
		Vector3 unitAxis = pAxis / pAxis.Length();

		Elements[0] += tanTheta * unitAxis.X * unitAxis.X + cosTheta;
		Elements[4] += tanTheta * unitAxis.Y * unitAxis.X + sinTheta * unitAxis.Z;
		Elements[9] += tanTheta * unitAxis.Z * unitAxis.X - sinTheta * unitAxis.Y;

		Elements[1] += tanTheta * unitAxis.X * unitAxis.Y - sinTheta * unitAxis.Z;
		Elements[5] += tanTheta * unitAxis.Y * unitAxis.Y + cosTheta;
		Elements[10] += tanTheta * unitAxis.Z * unitAxis.Y + sinTheta * unitAxis.X;

		Elements[2] += tanTheta * unitAxis.X * unitAxis.Z + sinTheta * unitAxis.Y;
		Elements[6] += tanTheta * unitAxis.Y * unitAxis.Z - sinTheta * unitAxis.X;
		Elements[11] += tanTheta * unitAxis.Z * unitAxis.Z + cosTheta;
	}

	void Matrix4::RotateX(const float pAngle)
	{
		float sinTheta = sinf(pAngle);
		float cosTheta = cosf(pAngle);

		Elements[5] += cosTheta;
		Elements[6] += sinTheta;
		Elements[9] += -sinTheta;
		Elements[10] += cosTheta;
	}

	void Matrix4::RotateY(const float pAngle)
	{
		float sinTheta = sinf(pAngle);
		float cosTheta = cosf(pAngle);

		Elements[0] += cosTheta;
		Elements[2] += -sinTheta;
		Elements[8] += sinTheta;
		Elements[10] += cosTheta;
	}

	void Matrix4::RotateZ(const float pAngle)
	{
		float sinTheta = sinf(pAngle);
		float cosTheta = cosf(pAngle);

		Elements[0] += cosTheta;
		Elements[1] += sinTheta;
		Elements[4] += -sinTheta;
		Elements[5] += cosTheta;
	}

	void Matrix4::Scale(const float pX, const float pY, const float pZ)
	{
		Elements[0] *= pX;
		Elements[5] *= pY;
		Elements[10] *= pZ;
	}

	void Matrix4::Scale(const float pScalar)
	{
		Elements[0] *= pScalar;
		Elements[5] *= pScalar;
		Elements[10] *= pScalar;
	}

	void Matrix4::Scale(const Vector3& pVector)
	{
		Scale(pVector.X, pVector.Y, pVector.Z);
	}

	float Matrix4::Determinant()
	{
		return Elements[0] * Elements[5] * Elements[10] * Elements[15] + Elements[0] * Elements[6] * Elements[11] * Elements[13] + Elements[0] * Elements[7] * Elements[9] * Elements[14]
			+ Elements[1] * Elements[4] * Elements[11] * Elements[14] + Elements[1] * Elements[6] * Elements[8] * Elements[15] + Elements[1] * Elements[7] * Elements[10] * Elements[12]
			+ Elements[2] * Elements[4] * Elements[9] * Elements[15] + Elements[2] * Elements[5] * Elements[11] * Elements[12] + Elements[2] * Elements[7] * Elements[8] * Elements[13]
			+ Elements[3] * Elements[4] * Elements[10] * Elements[13] + Elements[3] * Elements[5] * Elements[8] * Elements[14] + Elements[3] * Elements[6] * Elements[9] * Elements[12]
			- Elements[0] * Elements[5] * Elements[11] * Elements[14] - Elements[0] * Elements[6] * Elements[9] * Elements[15] - Elements[0] * Elements[7] * Elements[10] * Elements[13]
			- Elements[1] * Elements[4] * Elements[10] * Elements[15] - Elements[1] * Elements[6] * Elements[11] * Elements[12] - Elements[1] * Elements[7] * Elements[8] * Elements[14]
			- Elements[2] * Elements[4] * Elements[11] * Elements[13] - Elements[2] * Elements[5] * Elements[8] * Elements[15] - Elements[2] * Elements[7] * Elements[9] * Elements[12]
			- Elements[3] * Elements[4] * Elements[9] * Elements[14] - Elements[3] * Elements[5] * Elements[10] * Elements[12] - Elements[3] * Elements[6] * Elements[8] * Elements[13];
	}

	void Matrix4::Invert()
	{
		float det = Determinant();

		if (det != 0.0f)
		{
			float M11 = Elements[0];
			float M12 = Elements[1];
			float M13 = Elements[2];
			float M14 = Elements[3];
			float M21 = Elements[4];
			float M22 = Elements[5];
			float M23 = Elements[6];
			float M24 = Elements[7];
			float M31 = Elements[8];
			float M32 = Elements[9];
			float M33 = Elements[10];
			float M34 = Elements[11];
			float M41 = Elements[12];
			float M42 = Elements[13];
			float M43 = Elements[14];
			float M44 = Elements[15];

			float b11 = M22 * M33 * M44	+ M23 * M34 * M42 + M24 * M32 * M43 - M22 * M34 * M43 - M23 * M32 * M44 - M24 * M33 * M42;
			float b12 = M12 * M34 * M43 + M13 * M32 * M44 + M14 * M33 * M42 - M12 * M33 * M44 - M13 * M34 * M42 - M14 * M32 * M43;
			float b13 = M12 * M23 * M44 + M13 * M24 * M42 + M14 * M22 * M42 - M12 * M24 * M43 - M13 * M22 * M44 - M14 * M23 * M42;
			float b14 = M12 * M24 * M33 + M13 * M22 * M34 + M14 * M23 * M32 - M12 * M23 * M34 - M13 * M24 * M32 - M14 * M22 * M33;
			float b21 = M21 * M34 * M43 + M23 * M31 * M44 + M24 * M33 * M41 - M21 * M33 * M44 - M23 * M34 * M41 - M24 * M31 * M43;
			float b22 = M11 * M33 * M44 + M13 * M34 * M41 + M14 * M31 * M43 - M11 * M34 * M43 - M13 * M31 * M44 - M14 * M33 * M41;
			float b23 = M11 * M24 * M43 + M13 * M21 * M44 + M14 * M23 * M41 - M11 * M23 * M44 - M13 * M24 * M41 - M14 * M21 * M43;
			float b24 = M11 * M23 * M34 + M13 * M24 * M31 + M14 * M21 * M33 - M11 * M24 * M33 - M13 * M21 * M34 - M14 * M23 * M31;
			float b31 = M21 * M32 * M44 + M22 * M34 * M41 + M24 * M31 * M42 - M21 * M34 * M42 - M22 * M31 * M44 - M24 * M32 * M41;
			float b32 = M11 * M34 * M42 + M12 * M31 * M44 + M14 * M32 * M41 - M11 * M32 * M44 - M12 * M34 * M41 - M14 * M31 * M42;
			float b33 = M11 * M22 * M44 + M12 * M24 * M41 + M14 * M21 * M42 - M11 * M24 * M42 - M12 * M21 * M44 - M14 * M22 * M41;
			float b34 = M11 * M24 * M32 + M12 * M21 * M34 + M14 * M22 * M31 - M11 * M22 * M34 - M12 * M24 * M31 - M14 * M21 * M32;
			float b41 = M21 * M33 * M42 + M22 * M31 * M43 + M23 * M32 * M41 - M21 * M32 * M43 - M22 * M33 * M41 - M23 * M31 * M42;
			float b42 = M11 * M32 * M43 + M12 * M33 * M41 + M13 * M31 * M42 - M11 * M33 * M42 - M12 * M31 * M43 - M13 * M32 * M41;
			float b43 = M11 * M23 * M42 + M12 * M21 * M43 + M13 * M22 * M41 - M11 * M22 * M43 - M12 * M23 * M41 - M13 * M21 * M42;
			float b44 = M11 * M22 * M33 + M12 * M23 * M31 + M13 * M21 * M32 - M11 * M23 * M32 - M12 * M21 * M33 - M13 * M22 * M31;

			Elements[0] = b11 / det;
			Elements[1] = b12 / det;
			Elements[2] = b13 / det;
			Elements[3] = b14 / det;
			Elements[4] = b21 / det;
			Elements[5] = b22 / det;
			Elements[6] = b23 / det;
			Elements[7] = b24 / det;
			Elements[8] = b31 / det;
			Elements[9] = b32 / det;
			Elements[10] = b33 / det;
			Elements[11] = b34 / det;
			Elements[12] = b41 / det;
			Elements[13] = b42 / det;
			Elements[14] = b43 / det;
			Elements[15] = b44 / det;
		}
	}

	// static
	Matrix4 Matrix4::FromTranslation(float pX, float pY, float pZ)
	{
		Matrix4 matrix;
		matrix.Elements[0] = 1.0f;
		matrix.Elements[1] = 0.0f;
		matrix.Elements[2] = 0.0f;
		matrix.Elements[3] = pX;
		matrix.Elements[4] = 0.0f;
		matrix.Elements[5] = 1.0f;
		matrix.Elements[6] = 0.0f;
		matrix.Elements[7] = pY;
		matrix.Elements[8] = 0.0f;
		matrix.Elements[9] = 0.0f;
		matrix.Elements[10] = 1.0f;
		matrix.Elements[11] = pZ;
		matrix.Elements[12] = 0.0f;
		matrix.Elements[13] = 0.0f;
		matrix.Elements[14] = 0.0f;
		matrix.Elements[15] = 1.0f;

		return matrix;
	}

	// static
	Matrix4 Matrix4::FromPitchYawRoll(float pPitch, float pYaw, float pRoll)
	{
		float cosX = cosf(pPitch);
		float sinX = sinf(pPitch);
		float cosY = cosf(pYaw);
		float sinY = sinf(pYaw);
		float cosZ = cosf(pRoll);
		float sinZ = sinf(pRoll);

		// phi φ = X
		// theta θ = Y
		// psi ψ = Z

		Matrix4 matrix;
		matrix.Elements[0] = cosY * cosZ;
		matrix.Elements[1] = -cosX * sinZ + sinX * sinY * cosZ;
		matrix.Elements[2] = sinX * sinZ + cosX * sinY * cosZ;
		matrix.Elements[3] = 0.0f;
		matrix.Elements[4] = cosY * sinZ;
		matrix.Elements[5] = cosX * cosZ + sinX * sinY * sinZ;
		matrix.Elements[6] = -sinX * cosZ + cosX * sinY * sinZ;
		matrix.Elements[7] = 0.0f;
		matrix.Elements[8] = -sinY;
		matrix.Elements[9] = sinX * cosY;
		matrix.Elements[10] = cosX * cosY;
		matrix.Elements[11] = 0.0f;
		matrix.Elements[12] = 0.0f;
		matrix.Elements[13] = 0.0f;
		matrix.Elements[14] = 0.0f;
		matrix.Elements[15] = 1.0f;

		return matrix;
	}

	// static
	Matrix4 Matrix4::FromScale(float pX, float pY, float pZ)
	{
		Matrix4 matrix;
		matrix.Elements[0] = pX;
		matrix.Elements[1] = 0.0f;
		matrix.Elements[2] = 0.0f;
		matrix.Elements[3] = 1.0f;
		matrix.Elements[4] = 0.0f;
		matrix.Elements[5] = pY;
		matrix.Elements[6] = 0.0f;
		matrix.Elements[7] = 1.0f;
		matrix.Elements[8] = 0.0f;
		matrix.Elements[9] = 0.0f;
		matrix.Elements[10] = pZ;
		matrix.Elements[11] = 1.0f;
		matrix.Elements[12] = 0.0f;
		matrix.Elements[13] = 0.0f;
		matrix.Elements[14] = 0.0f;
		matrix.Elements[15] = 1.0f;

		return matrix;
	}

	// static
	bool Matrix4::Inverse(const Matrix4& pIn, Matrix4& pOut)
	{
		return false;
	}
}
