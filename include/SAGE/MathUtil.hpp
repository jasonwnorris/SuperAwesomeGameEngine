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

			static void Seed(unsigned int pSeed) { srand(pSeed); }
			static int Random(int pMin, int pMax) { return rand() % (pMax - pMin + 1) + pMin; }
			static float Random(float pMin, float pMax) { return (float)rand() / (float)RAND_MAX * (pMax - pMin) + pMin; }
			static double Random(double pMin, double pMax) { return (double)rand() / (double)RAND_MAX * (pMax - pMin) + pMin; }

			template<typename T> static T Min(T pA, T pB) { return pA < pB ? pA : pB; }
			static int Min(int pA, int pB) { return pA < pB ? pA : pB; }
			static float Min(float pA, float pB) { return pA < pB ? pA : pB; }
			static double Min(double pA, double pB) { return pA < pB ? pA : pB; }

			template<typename T> static T Max(T pA, T pB) { return pA > pB ? pA : pB; }
			static int Max(int pA, int pB) { return pA > pB ? pA : pB; }
			static float Max(float pA, float pB) { return pA > pB ? pA : pB; }
			static double Max(double pA, double pB) { return pA > pB ? pA : pB; }

			static int Abs(int pValue) { return pValue < 0 ? -pValue : pValue; }
			static float Abs(float pValue) { return pValue < 0.0f ? -pValue : pValue; }
			static double Abs(double pValue) { return pValue < 0.0 ? -pValue : pValue; }
			template<typename T> static T Abs(T pValue) { return pValue < 0 ? -pValue : pValue; }

			static int SignOf(int pValue) { return pValue / Abs(pValue); }
			static float SignOf(float pValue) { return pValue / Abs(pValue); }
			static double SignOf(double pValue) { return pValue / Abs(pValue); }
			template<typename T> static T SignOf(T pValue) { return pValue / Abs(pValue); }

			static float Lerp(float pValueA, float pValueB, float pAmount)
			{
				if (pAmount < 0)
					return pValueA;
				if (pAmount > 1)
					return pValueB;

				return pValueA + ((pValueB - pValueA) * pAmount);
			}

			template<typename T> static T Clamp(T pValue, T pMin, T pMax)
			{
				if (pValue < pMin) pValue = pMin;
				if (pValue > pMax) pValue = pMax;

				return pValue;
			}

			static float ToRadians(float pDegrees)
			{
				return pDegrees / 180.0f * Pi;
			}

			static float ToDegrees(float pRadians)
			{
				return pRadians / Pi * 180.0f;
			}

			static int Factorial(int pValue)
			{
				if (pValue > 0)
				{
					int value = 1;

					for (int i = 0; i < pValue; i++)
						value *= (i + 1);

					return value;
				}
				else if (pValue < 0)
				{
					return 0;
				}
				else
				{
					return 1;
				}
			}

			static bool IsPO2(int pNumber)
			{
				return (pNumber & (pNumber - 1)) != 0;
			}

			static int NextPO2(int pNumber)
			{
				int next = 1;

				while (next < pNumber)
					next *= 2;

				return next;
			}
	};
}

#endif
