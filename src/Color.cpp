// Color.cpp

// OpenGL Includes
#include <gl\glew.h>
// SDL Includes
#include <SDL2\SDL.h>
// SAGE Includes
#include <SAGE\Color.hpp>
#include <SAGE\MathUtil.hpp>
// STD Includes
#include <string>

namespace SAGE
{
	const Color Color::White = Color(1.0f, 1.0f, 1.0f, 1.0f);
	const Color Color::LightGray = Color(0.75f, 0.75f, 0.75f, 1.0f);
	const Color Color::Gray = Color(0.5f, 0.5f, 0.5f, 1.0f);
	const Color Color::DarkGray = Color(0.25f, 0.25f, 0.25f, 1.0f);
	const Color Color::Black = Color(0.0f, 0.0f, 0.0f, 1.0f);
	const Color Color::Red = Color(1.0f, 0.0f, 0.0f, 1.0f);
	const Color Color::Green = Color(0.0f, 1.0f, 0.0f, 1.0f);
	const Color Color::Blue = Color(0.0f, 0.0f, 1.0f, 1.0f);
	const Color Color::Cyan = Color(0.0f, 1.0f, 1.0f, 1.0f);
	const Color Color::Magenta = Color(1.0f, 0.0f, 1.0f, 1.0f);
	const Color Color::Yellow = Color(1.0f, 1.0f, 0.0f, 1.0f);
	const Color Color::Orange = Color(1.0f, 0.5f, 0.0f, 1.0f);
	const Color Color::Purple = Color(0.5f, 0.0f, 0.5f, 1.0f);
	const Color Color::Maroon = Color(0.5f, 0.0f, 0.0f, 1.0f);
	const Color Color::Olive = Color(0.0f, 0.5f, 0.0f, 1.0f);
	const Color Color::Navy = Color(0.0f, 0.0f, 0.5f, 1.0f);
	const Color Color::TransparentWhite = Color(1.0f, 1.0f, 1.0f, 0.0f);
	const Color Color::TransparentBlack = Color(0.0f, 0.0f, 0.0f, 0.0f);

	Color::Color()
	{
		mRed = 1.0f;
		mGreen = 1.0f;
		mBlue = 1.0f;
		mAlpha = 1.0f;
	}

	Color::Color(float pRed, float pGreen, float pBlue, float pAlpha)
	{
		mRed = pRed;
		mGreen = pGreen;
		mBlue = pBlue;
		mAlpha = pAlpha;
	}

	Color::Color(const char* pHex, float pAlpha)
	{
		int value = std::stoi(pHex, 0, 16);

		mRed = (float)((value >> 16) & 0xFF) / 255.0f;
		mGreen = (float)((value >> 8) & 0xFF) / 255.0f;;
		mBlue = (float)(value & 0xFF) / 255.0f;;
		mAlpha = pAlpha;
	}

	bool Color::operator==(const Color& pColor) const
	{
		return mRed == pColor.GetRed() && mGreen == pColor.GetGreen() && mBlue == pColor.GetBlue() && mAlpha == pColor.GetAlpha();
	}

	bool Color::operator!=(const Color& pColor) const
	{
		return mRed != pColor.GetRed() || mGreen != pColor.GetGreen() || mBlue != pColor.GetBlue() || mAlpha != pColor.GetAlpha();
	}

	Color& Color::operator=(const Color& pColor)
	{
		mRed = pColor.GetRed();
		mGreen = pColor.GetGreen();
		mBlue = pColor.GetBlue();
		mAlpha = pColor.GetAlpha();

		return *this;
	}

	Color Color::operator+(const Color& pColor) const
	{
		return Color(mRed + pColor.GetRed(), mGreen + pColor.GetGreen(), mBlue + pColor.GetBlue(), mAlpha);
	}

	Color Color::operator-(const Color& pColor) const
	{
		return Color(mRed - pColor.GetRed(), mGreen - pColor.GetGreen(), mBlue - pColor.GetBlue(), mAlpha);
	}

	Color Color::operator*(float pScalar) const
	{
		return Color(mRed * pScalar, mGreen * pScalar, mBlue * pScalar, mAlpha);
	}

	Color Color::operator/(float pScalar) const
	{
		return Color(mRed / pScalar, mGreen / pScalar, mBlue / pScalar, mAlpha);
	}

	Color& Color::operator+=(const Color& pColor)
	{
		mRed += pColor.GetRed();
		mGreen += pColor.GetGreen();
		mBlue += pColor.GetBlue();

		return *this;
	}

	Color& Color::operator-=(const Color& pColor)
	{
		mRed -= pColor.GetRed();
		mGreen -= pColor.GetGreen();
		mBlue -= pColor.GetBlue();

		return *this;
	}

	Color& Color::operator*=(float pScalar)
	{
		mRed *= pScalar;
		mGreen *= pScalar;
		mBlue *= pScalar;

		return *this;
	}

	Color& Color::operator/=(float pScalar)
	{
		mRed /= pScalar;
		mGreen /= pScalar;
		mBlue /= pScalar;

		return *this;
	}

	float Color::GetRed() const
	{
		return mRed;
	}

	float Color::GetGreen() const
	{
		return mGreen;
	}

	float Color::GetBlue() const
	{
		return mBlue;
	}

	float Color::GetAlpha() const
	{
		return mAlpha;
	}

	void Color::SetRed(float pRed)
	{
		mRed = pRed;
	}

	void Color::SetGreen(float pGreen)
	{
		mGreen = pGreen;
	}

	void Color::SetBlue(float pBlue)
	{
		mBlue = pBlue;
	}

	void Color::SetAlpha(float pAlpha)
	{
		mAlpha = pAlpha;
	}

	void Color::SetOpenGL() const
	{
		glColor4f(mRed, mGreen, mBlue, mAlpha);
	}

	Color& Color::Invert(bool pInvertAlpha)
	{
		mRed = 1.0f - mRed;
		mGreen = 1.0f - mGreen;
		mBlue = 1.0f - mBlue;
		mAlpha = pInvertAlpha ? 1.0f - mAlpha : mAlpha;

		return *this;
	}

	Color Color::Inverse(bool pInvertAlpha) const
	{
		return Color(1.0f - mRed, 1.0f - mGreen, 1.0f - mBlue, pInvertAlpha ? 1.0f - mAlpha : mAlpha);
	}

	// static
	Color Color::Lerp(const Color& pColorA, const Color& pColorB, float pAmount)
	{
		return Color(MathUtil::Lerp(pColorA.GetRed(), pColorB.GetRed(), pAmount),
					 MathUtil::Lerp(pColorA.GetGreen(), pColorB.GetGreen(), pAmount),
					 MathUtil::Lerp(pColorA.GetBlue(), pColorB.GetBlue(), pAmount),
					 MathUtil::Lerp(pColorA.GetAlpha(), pColorB.GetAlpha(), pAmount));
	}
}
