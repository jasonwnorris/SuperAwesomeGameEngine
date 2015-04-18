// SpriteBatch.hpp

#ifndef __SAGE_SPRITEBATCH_HPP__
#define __SAGE_SPRITEBATCH_HPP__

// SAGE Includes
#include <SAGE\Orientation.hpp>
#include <SAGE\VertexDefinitions.hpp>
// HGF Includes
#include <HGF\Color.hpp>
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

	enum class SamplerState
	{
		PointClamp,
		PointWrap,
		LinearClamp,
		LinearWrap,
		AnisotropicClamp,
		AnisotropicWrap,
	};

	enum class DepthStencilState
	{
		None,
		Default,
		DepthRead,
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

			bool Initialize();
			bool Finalize();

			int GetDrawCallCount() const;
			bool Begin(SortMode pSortMode = SortMode::None, BlendMode pBlendMode = BlendMode::None, SamplerState pSamplerState = SamplerState::LinearClamp, DepthStencilState pDepthStencilState = DepthStencilState::Default, RasterizerState pRasterizerState = RasterizerState::CullCounterClockwise);
			bool Draw(const HGF::Texture& pTexture, const HGF::Vector2& pPosition, const HGF::Rectangle& pSource, const HGF::Color& pColor, const HGF::Vector2& pOrigin, float pRotation, const HGF::Vector2& pScale, Orientation pOrientation, float pDepth = 0.0f);
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

			bool mWithinDrawPair;
			int mFlushCount;
			SortMode mSortMode;
			BlendMode mBlendMode;
			SamplerState mSamplerState;
			DepthStencilState mDepthStencilState;
			RasterizerState mRasterizerState;
			int mBufferIndex;
			GLuint mVertexArrayObject[RingBufferCount];
			GLuint mVertexBufferObject[RingBufferCount];
			GLuint mIndexBufferObject;
			std::vector<SpriteBatchItem> mBatchItemList;
			std::vector<VertexPositionColorTexture> mVertexBuffer;
	};
}

#endif