// MathUtil.hpp

#ifndef __SAGE_MATHUTIL_HPP__
#define __SAGE_MATHUTIL_HPP__

// STD Includes
#include <math.h>
#include <cstdlib>

namespace SAGE
{
	class MathUtil
	{
		public:
			static float Pi;
			static float TwoPi;
			static float PiOver2;
			static float PiOver4;
			static float E;
			static float Epsilon;

			static void Seed(unsigned int p_Seed) { srand(p_Seed); }
			static int Random(int p_Min, int p_Max) { return rand() % (p_Max - p_Min + 1) + p_Min; }
			static float Random(float p_Min, float p_Max) { return (float)rand() / (float)RAND_MAX * (p_Max - p_Min) + p_Min; }
			static double Random(double p_Min, double p_Max) { return (double)rand() / (double)RAND_MAX * (p_Max - p_Min) + p_Min; }

			template<typename T> static T Min(T p_A, T p_B) { return p_A < p_B ? p_A : p_B; }
			static int Min(int p_A, int p_B) { return p_A < p_B ? p_A : p_B; }
			static float Min(float p_A, float p_B) { return p_A < p_B ? p_A : p_B; }
			static double Min(double p_A, double p_B) { return p_A < p_B ? p_A : p_B; }

			template<typename T> static T Max(T p_A, T p_B) { return p_A > p_B ? p_A : p_B; }
			static int Max(int p_A, int p_B) { return p_A > p_B ? p_A : p_B; }
			static float Max(float p_A, float p_B) { return p_A > p_B ? p_A : p_B; }
			static double Max(double p_A, double p_B) { return p_A > p_B ? p_A : p_B; }

			static int Abs(int p_Value) { return p_Value < 0 ? -p_Value : p_Value; }
			static float Abs(float p_Value) { return p_Value < 0.0f ? -p_Value : p_Value; }
			static double Abs(double p_Value) { return p_Value < 0.0 ? -p_Value : p_Value; }
			template<typename T> static T Abs(T p_Value) { return p_Value < 0 ? -p_Value : p_Value; }

			static int SignOf(int p_Value) { return p_Value / Abs(p_Value); }
			static float SignOf(float p_Value) { return p_Value / Abs(p_Value); }
			static double SignOf(double p_Value) { return p_Value / Abs(p_Value); }
			template<typename T> static T SignOf(T p_Value) { return p_Value / Abs(p_Value); }

			static float Lerp(float p_ValueA, float p_ValueB, float p_Amount)
			{
				if (p_Amount < 0)
					return p_ValueA;
				if (p_Amount > 1)
					return p_ValueB;

				return p_ValueA + ((p_ValueB - p_ValueA) * p_Amount);
			}

			template<typename T> static T Clamp(T p_Value, T p_Min, T p_Max)
			{
				if (p_Value < p_Min) p_Value = p_Min;
				if (p_Value > p_Max) p_Value = p_Max;

				return p_Value;
			}

			static float ToRadians(float p_Degrees)
			{
				return p_Degrees / 180.0f * Pi;
			}

			static float ToDegrees(float p_Radians)
			{
				return p_Radians / Pi * 180.0f;
			}

			static int Factorial(int p_Value)
			{
				if (p_Value > 0)
				{
					int value = 1;

					for (int i = 0; i < p_Value; i++)
						value *= (i + 1);

					return value;
				}
				else if (p_Value < 0)
				{
					return 0;
				}
				else
				{
					return 1;
				}
			}

			static bool IsPO2(int p_Number)
			{
				return (p_Number & (p_Number - 1)) != 0;
			}

			static int NextPO2(int p_Number)
			{
				int next = 1;

				while (next < p_Number)
					next *= 2;

				return next;
			}
	};
}

#endif
