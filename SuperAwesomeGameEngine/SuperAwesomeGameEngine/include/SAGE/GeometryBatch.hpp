// GeometryBatch.hpp

#ifndef __SAGE_GEOMETRYBATCH_HPP__
#define __SAGE_GEOMETRYBATCH_HPP__

// SAGE Includes
#include <SAGE\Camera2D.hpp>
#include <SAGE\VertexDefinitions.hpp>
// HGF Includes
#include <HGF\Color.hpp>
#include <HGF\Effect.hpp>
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

			bool Initialize();
			bool Finalize();

			int GetDrawCallCount() const;
			bool Begin(HGF::Effect& pEffect, const Camera2D& pCamera = Camera2D::DefaultCamera);
			bool Draw(const HGF::Vector2& pPositionA, const HGF::Vector2& pPositionB, const HGF::Color& pColor);
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