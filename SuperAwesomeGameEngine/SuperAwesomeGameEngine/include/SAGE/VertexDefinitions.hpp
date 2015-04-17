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

	struct VertexVector3
	{
		float X;
		float Y;
		float Z;
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
		VertexVector3 Position;
		VertexColor Color;
	};

	struct VertexPositionColorTexture
	{
		VertexVector3 Position;
		VertexColor Color;
		VertexVector2 TexCoord;
	};
}

#endif