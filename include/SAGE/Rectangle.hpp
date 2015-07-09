// Rectangle.hpp

#ifndef __SAGE_RECTANGLE_HPP__
#define __SAGE_RECTANGLE_HPP__

namespace SAGE
{
	class Rectangle
	{
		public:
			static const Rectangle Empty;

			Rectangle() { X = 0; Y = 0; Width = 0; Height = 0; }
			Rectangle(int pX, int pY, int pWidth, int pHeight) { X = pX; Y = pY; Width = pWidth; Height = pHeight; }
			~Rectangle() { }

			bool operator==(const Rectangle& pOther) const { return X == pOther.X && Y == pOther.Y && Width == pOther.Width && Height == pOther.Height; }
			bool operator!=(const Rectangle& pOther) const { return !(*this == pOther); }

			int X;
			int Y;
			int Width;
			int Height;
	};
}

#endif
