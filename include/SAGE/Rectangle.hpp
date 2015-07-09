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
			Rectangle(int p_X, int p_Y, int p_Width, int p_Height) { X = p_X; Y = p_Y; Width = p_Width; Height = p_Height; }
			~Rectangle() { }

			bool operator==(const Rectangle& p_Other) const { return X == p_Other.X && Y == p_Other.Y && Width == p_Other.Width && Height == p_Other.Height; }
			bool operator!=(const Rectangle& p_Other) const { return !(*this == p_Other); }

			int X;
			int Y;
			int Width;
			int Height;
	};
}

#endif
