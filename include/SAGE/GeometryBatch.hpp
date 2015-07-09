// GeometryBatch.hpp

#ifndef __SAGE_GEOMETRYBATCH_HPP__
#define __SAGE_GEOMETRYBATCH_HPP__

// SAGE Includes
#include <SAGE\Camera2D.hpp>
#include <SAGE\VertexDefinitions.hpp>
// SAGE Includes
#include <SAGE\Color.hpp>
#include <SAGE\Effect.hpp>
#include <SAGE\Rectangle.hpp>
#include <SAGE\Vector2.hpp>
// STL Includes
#include <vector>

namespace SAGE
{
	class GeometryBatch
	{
		private:
			static const int MaxBatchSize = 1024;
			static const int MaxVertexCount = MaxBatchSize * 4;
			static const int MaxIndexCount = MaxBatchSize * 4;

		public:
			GeometryBatch();
			~GeometryBatch();

			int GetDrawCallCount() const;

			bool Initialize();
			bool Finalize();

			bool Begin(Effect& p_Effect, const Camera2D& p_Camera = Camera2D::DefaultCamera);
			bool DrawLine(const Vector2& p_PositionA, const Vector2& p_PositionB, const Color& p_Color);
			bool DrawLines(const std::vector<Vector2>& p_Positions, const Color& p_Color);
			bool DrawRectangle(const Vector2& p_TopLeft, const Vector2& p_BottomRight, const Color& p_Color);
			bool DrawRectangle(const Rectangle& p_Rectangle, const Color& p_Color);
			bool DrawCircle(const Vector2& p_Position, float p_Radius, const Color& p_Color, int p_Count = 25);
			bool DrawBezier(const Vector2& p_StartPosition, const Vector2& p_EndPosition, const Vector2& p_ControlPoint, const Color& p_Color, int p_Count = 25);
			bool DrawBezier(const Vector2& p_StartPosition, const Vector2& p_EndPosition, const Vector2& p_ControlPointA, const Vector2& p_ControlPointB, const Color& p_Color, int p_Count = 25);
			bool End();

		private:
			struct GeometryBatchItem
			{
				VertexPositionColor VertexA;
				VertexPositionColor VertexB;
			};

			void Render();
			void Flush(int p_Length);

			bool m_WithinDrawPair;
			int m_ItemCount;
			int m_FlushCount;
			GLuint m_VertexArrayObject;
			GLuint m_VertexBufferObject;
			GLuint m_IndexBufferObject;
			GeometryBatchItem m_BatchItemList[MaxBatchSize];
			VertexPositionColor m_VertexBuffer[MaxVertexCount];
	};
}

#endif
