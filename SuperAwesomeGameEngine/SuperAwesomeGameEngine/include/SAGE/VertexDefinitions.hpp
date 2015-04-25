// VertexDefinitions.hpp

#ifndef __SAGE_VERTEXDEFINITIONS_HPP__
#define __SAGE_VERTEXDEFINITIONS_HPP__

namespace SAGE
{
	struct VertexVector2
	{
		float X;
		float Y;
	};

	struct VertexColor
	{
		float R;
		float G;
		float B;
		float A;
	};

	struct VertexPositionColor
	{
		VertexVector2 Position;
		VertexColor Color;
	};

	struct VertexPositionColorTexture
	{
		VertexVector2 Position;
		VertexColor Color;
		VertexVector2 TexCoord;
	};
}

#endif