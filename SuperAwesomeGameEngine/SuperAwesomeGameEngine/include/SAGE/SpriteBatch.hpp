// SpriteBatch.hpp

#ifndef __SAGE_SPRITEBATCH_HPP__
#define __SAGE_SPRITEBATCH_HPP__

// SAGE Includes
#include <SAGE\Camera2D.hpp>
#include <SAGE\Orientation.hpp>
#include <SAGE\SpriteFont.hpp>
#include <SAGE\VertexDefinitions.hpp>
// HGF Includes
#include <HGF\Color.hpp>
#include <HGF\Effect.hpp>
#include <HGF\Rectangle.hpp>
#include <HGF\Texture.hpp>
#include <HGF\Vector2.hpp>
// STL Includes
#include <vector>

namespace SAGE
{
	enum class SortMode
	{
		None,
		FrontToBack,
		BackToFront,
		Texture,
		Immediate,
	};

	enum class BlendMode
	{
		None,
		Premultiplied,
		Additive,
		AlphaBlended,
	};

	enum class RasterizerState
	{
		None,
		CullClockwise,
		CullCounterClockwise,
	};

	class SpriteBatch
	{
		private:
			static const int MaxBatchSize = 1024;
			static const int MaxVertexCount = MaxBatchSize * 4;
			static const int MaxIndexCount = MaxVertexCount / 2 * 3;
			static const int RingBufferCount = 3;

		public:
			SpriteBatch();
			~SpriteBatch();

			int GetDrawCallCount() const;

			bool Initialize();
			bool Finalize();

			bool Begin(HGF::Effect& pEffect, const Camera2D& pCamera = Camera2D::DefaultCamera, SortMode pSortMode = SortMode::None, BlendMode pBlendMode = BlendMode::None, RasterizerState pRasterizerState = RasterizerState::CullCounterClockwise);
			
			bool Draw(const HGF::Texture& pTexture, const HGF::Vector2& pPosition, const HGF::Rectangle& pSource, const HGF::Color& pColor, const HGF::Vector2& pOrigin, float pRotation, const HGF::Vector2& pScale, Orientation pOrientation, float pDepth = 0.0f);
			bool DrawString(const SAGE::SpriteFont& pSpriteFont, const std::string& pString, const HGF::Vector2& pPosition, const HGF::Color& pColor, const HGF::Vector2& pOrigin, float pRotation, const HGF::Vector2& pScale, Orientation pOrientation, float pDepth = 0.0f);
			
			bool End();

		private:
			struct SpriteBatchItem
			{
				unsigned int TextureID;
				float Depth;
				VertexPositionColorTexture VertexTL;
				VertexPositionColorTexture VertexTR;
				VertexPositionColorTexture VertexBL;
				VertexPositionColorTexture VertexBR;
			};

			void Render();
			void Flush(int pTextureID, int pLength);

			void RotateAbout(const HGF::Vector2& pPosition, float pRotation, VertexVector2& pVertex);
			void FlipAbout(const HGF::Vector2& pPosition, Orientation pOrientation, VertexVector2& pVertex);

			bool mWithinDrawPair;
			int mItemCount;
			int mFlushCount;
			SortMode mSortMode;
			BlendMode mBlendMode;
			RasterizerState mRasterizerState;
			GLuint mVertexArrayObject;
			GLuint mVertexBufferObject;
			GLuint mIndexBufferObject;
			SpriteBatchItem mBatchItemList[MaxBatchSize];
			VertexPositionColorTexture mVertexBuffer[MaxVertexCount];
	};
}

#endif