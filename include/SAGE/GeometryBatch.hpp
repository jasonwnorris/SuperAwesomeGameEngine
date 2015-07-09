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

			bool Begin(Effect& pEffect, const Camera2D& pCamera = Camera2D::DefaultCamera);
			bool DrawLine(const Vector2& pPositionA, const Vector2& pPositionB, const Color& pColor);
			bool DrawLines(const std::vector<Vector2>& pPositions, const Color& pColor);
			bool DrawRectangle(const Vector2& pTopLeft, const Vector2& pBottomRight, const Color& pColor);
			bool DrawRectangle(const Rectangle& pRectangle, const Color& pColor);
			bool DrawCircle(const Vector2& pPosition, float pRadius, const Color& pColor, int pCount = 25);
			bool DrawBezier(const Vector2& pStartPosition, const Vector2& pEndPosition, const Vector2& pControlPoint, const Color& pColor, int pCount = 25);
			bool DrawBezier(const Vector2& pStartPosition, const Vector2& pEndPosition, const Vector2& pControlPointA, const Vector2& pControlPointB, const Color& pColor, int pCount = 25);
			bool End();

		private:
			struct GeometryBatchItem
			{
				VertexPositionColor VertexA;
				VertexPositionColor VertexB;
			};

			void Render();
			void Flush(int pLength);

			bool mWithinDrawPair;
			int mItemCount;
			int mFlushCount;
			GLuint mVertexArrayObject;
			GLuint mVertexBufferObject;
			GLuint mIndexBufferObject;
			GeometryBatchItem mBatchItemList[MaxBatchSize];
			VertexPositionColor mVertexBuffer[MaxVertexCount];
	};
}

#endif
