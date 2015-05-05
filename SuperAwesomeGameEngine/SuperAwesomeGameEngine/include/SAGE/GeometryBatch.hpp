// GeometryBatch.hpp

#ifndef __SAGE_GEOMETRYBATCH_HPP__
#define __SAGE_GEOMETRYBATCH_HPP__

// SAGE Includes
#include <SAGE\Camera2D.hpp>
#include <SAGE\VertexDefinitions.hpp>
// HGF Includes
#include <HGF\Color.hpp>
#include <HGF\Effect.hpp>
#include <HGF\Rectangle.hpp>
#include <HGF\Vector2.hpp>
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

			bool Begin(HGF::Effect& pEffect, const Camera2D& pCamera = Camera2D::DefaultCamera);
			bool DrawLine(const HGF::Vector2& pPositionA, const HGF::Vector2& pPositionB, const HGF::Color& pColor);
			bool DrawLines(const std::vector<HGF::Vector2>& pPositions, const HGF::Color& pColor);
			bool DrawRectangle(const HGF::Vector2& pTopLeft, const HGF::Vector2& pBottomRight, const HGF::Color& pColor);
			bool DrawRectangle(const HGF::Rectangle& pRectangle, const HGF::Color& pColor);
			bool DrawCircle(const HGF::Vector2& pPosition, float pRadius, const HGF::Color& pColor, int pCount = 25);
			bool DrawBezier(const HGF::Vector2& pStartPosition, const HGF::Vector2& pEndPosition, const HGF::Vector2& pControlPoint, const HGF::Color& pColor, int pCount = 25);
			bool DrawBezier(const HGF::Vector2& pStartPosition, const HGF::Vector2& pEndPosition, const HGF::Vector2& pControlPointA, const HGF::Vector2& pControlPointB, const HGF::Color& pColor, int pCount = 25);
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