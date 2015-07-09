// SpriteBatch.hpp

#ifndef __SAGE_SPRITEBATCH_HPP__
#define __SAGE_SPRITEBATCH_HPP__

// SAGE Includes
#include <SAGE\Camera2D.hpp>
#include <SAGE\Orientation.hpp>
#include <SAGE\SpriteFont.hpp>
#include <SAGE\VertexDefinitions.hpp>
// SAGE Includes
#include <SAGE\Color.hpp>
#include <SAGE\Effect.hpp>
#include <SAGE\Rectangle.hpp>
#include <SAGE\Texture.hpp>
#include <SAGE\Vector2.hpp>
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

			bool Begin(Effect& pEffect, const Camera2D& pCamera = Camera2D::DefaultCamera, SortMode pSortMode = SortMode::None, BlendMode pBlendMode = BlendMode::None, RasterizerState pRasterizerState = RasterizerState::CullCounterClockwise);

			bool Draw(const Texture& pTexture, const Vector2& pPosition, const Vector2& pDimensions, const Rectangle& pSourceRectangle, const Color& pColor, const Vector2& pOrigin, float pRotation, const Vector2& pScale, Orientation pOrientation, float pDepth = 0.0f);
			bool Draw(const Texture& pTexture, const Vector2& pPosition, const Rectangle& pDestinationRectangle, const Rectangle& pSourceRectangle, const Color& pColor, const Vector2& pOrigin, float pRotation, const Vector2& pScale, Orientation pOrientation, float pDepth = 0.0f);
			bool Draw(const Texture& pTexture, const Rectangle& pDestinationRectangle, const Rectangle& pSourceRectangle, const Color& pColor, const Vector2& pOrigin, float pRotation, const Vector2& pScale, Orientation pOrientation, float pDepth = 0.0f);
			bool Draw(const Texture& pTexture, const Vector2& pPosition, const Rectangle& pSourceRectangle, const Color& pColor, const Vector2& pOrigin, float pRotation, const Vector2& pScale, Orientation pOrientation, float pDepth = 0.0f);
			
			bool DrawString(const SAGE::SpriteFont& pSpriteFont, const std::string& pString, const Vector2& pPosition, const Color& pColor, float pDepth = 0.0f);
			bool DrawString(const SAGE::SpriteFont& pSpriteFont, const std::string& pString, const Vector2& pPosition, const Color& pColor, const Vector2& pOrigin, float pRotation, const Vector2& pScale, Orientation pOrientation, float pDepth = 0.0f);
			
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

			void RotateAbout(const Vector2& pPosition, float pRotation, VertexVector2& pVertex);
			void FlipAbout(const Vector2& pPosition, Orientation pOrientation, VertexVector2& pVertex);

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
