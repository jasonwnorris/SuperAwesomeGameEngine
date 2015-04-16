// VertexDefinitions.hpp

#ifndef __SAGE_VERTEXDEFINITIONS_HPP__
#define __SAGE_VERTEXDEFINITIONS_HPP__

// HGF Includes
#include <HGF\Color.hpp>
#include <HGF\Vector2.hpp>
#include <HGF\Vector3.hpp>

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

	struct VertexPositionColorNormal
	{
		VertexVector3 Position;
		VertexColor Color;
		VertexVector3 Normal;
	};

	struct VertexPositionColorTexture
	{
		VertexVector3 Position;
		VertexColor Color;
		VertexVector2 TexCoord;
	};

	struct VertexPositionColorNormalTexture
	{
		VertexVector3 Position;
		VertexColor Color;
		VertexVector3 Normal;
		VertexVector2 TexCoord;
	};
}

#endif