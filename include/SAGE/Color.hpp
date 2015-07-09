// Color.hpp

#ifndef __SAGE_COLOR_HPP_
#define __SAGE_COLOR_HPP_

namespace SAGE
{
	class Color
	{
		public:
			static const Color White;
			static const Color LightGray;
			static const Color Gray;
			static const Color DarkGray;
			static const Color Black;
			static const Color Red;
			static const Color Green;
			static const Color Blue;
			static const Color Cyan;
			static const Color Magenta;
			static const Color Yellow;
			static const Color Orange;
			static const Color Purple;
			static const Color Maroon;
			static const Color Olive;
			static const Color Navy;
			static const Color TransparentWhite;
			static const Color TransparentBlack;

			Color();
			Color(float pRed, float pGreen, float pBlue, float pAlpha = 1.0f);
			Color(const char* pHex, float pAlpha = 1.0f);
			~Color() = default;

			bool operator==(const Color& pColor) const;
			bool operator!=(const Color& pColor) const;
			Color& operator=(const Color& pColor);
			Color operator+(const Color& pColor) const;
			Color operator-(const Color& pColor) const;
			Color operator*(float pScalar) const;
			Color operator/(float pScalar) const;
			Color& operator+=(const Color& pColor);
			Color& operator-=(const Color& pColor);
			Color& operator*=(float pScalar);
			Color& operator/=(float pScalar);

			float GetRed() const;
			float GetGreen() const;
			float GetBlue() const;
			float GetAlpha() const;

			void SetRed(float pRed);
			void SetGreen(float pGreen);
			void SetBlue(float pBlue);
			void SetAlpha(float pAlpha);
			void SetOpenGL() const;

			Color& Invert(bool pInvertAlpha = false);
			Color Inverse(bool pInvertAlpha = false) const;

			static Color Lerp(const Color& pColorA, const Color& pColorB, float pAmount);

		private:
			float mRed;
			float mGreen;
			float mBlue;
			float mAlpha;
	};
}

#endif
